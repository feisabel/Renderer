#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

#include "../include/scene.h"
#include "../include/sphere.h"
#include "../include/camera.h"
#include "../include/image.h"

void init(Scene* scene, Image* image, Camera* camera) {
    //add background and spheres to the scene
    scene->set_background(rgb(0.5, 0.7, 1), rgb(0.5, 0.7, 1), rgb(1, 1, 1), rgb(1, 1, 1));
    scene->add_hitable(new Sphere(point3( 0, 0, -1 ), 0.5));
    scene->add_hitable(new Sphere(point3( 0, -100.5, -1 ), 100));
    scene->add_hitable(new Sphere(point3( 0.5, 0, -1.4 ), 0.5));
    scene->add_hitable(new Sphere(point3( -0.3, 0, -0.6 ), 0.4));

    //scene->add_hitable(new Sphere(point3( 1, 0, -1.5 ), 0.5));
    //scene->add_hitable(new Sphere(point3( -1.2, 0, -1.3 ), 0.5));

    //scene->add_hitable(new Sphere(point3( 0, -100.5, -3 ), 99));
    //scene->add_hitable(new Sphere(point3( 0.3, 0, -1 ), 0.4));
    //scene->add_hitable(new Sphere(point3( 0, 1, -2 ), 0.6));
    //scene->add_hitable(new Sphere(point3( -0.4, 0, -3 ), 0.7));

    //add image information
    image->set_dimensions(2000, 1000);
    image->set_name("images/depth_spheres.ppm");
    image->set_codification("binary");

    //add camera information
    camera->set_things(point3(-2, -1, -1), vec3(4, 0, 0), vec3(0, 2, 0), point3(0, 0, 0));

}

void write_file(Image* image, char* buffer) {
    std::ofstream image_file (image->get_name());
    if (image_file.is_open()) {
        if (image->get_codification().compare("binary") == 0) {
            image_file << "P6\n";
            image_file << image->get_width() << " " << image->get_height() << "\n";
            image_file << "255\n";
            image_file.write(buffer, image->get_width() * image->get_height() * 3);
        }
        else {
            image_file << "P3\n";
            image_file << image->get_width() << " " << image->get_height() << "\n";
            image_file << "255\n";
            for (int i = 0; i < image->get_width() * image->get_height() * 3; i+=3) {
                image_file << int((unsigned char )buffer[i]) << " " 
                                << int((unsigned char )buffer[i+1]) << " " 
                                << int((unsigned char )buffer[i+2]) << "\n";
            }
        }

        image_file.close();
    }
}

rgb normal_color(Ray ray, Scene* scene) {
    hit_record rec;

    if (scene->hit(ray, 0, std::numeric_limits<float>::max(), rec)) {
        //colors the spheres with their normals
        return (rec.normal + vec3(1, 1, 1))/2;
    }
    else {
        vec3 unit_ray = unit_vector(ray.get_direction());
        float x_ratio = (unit_ray.x()+1.0)/2.0;
        float y_ratio = (unit_ray.y()+1.0)/2.0;

        //colors the background with bilinear interpolation
        rgb left = lerp(y_ratio, scene->get_background_upper_left(), scene->get_background_lower_left());
        rgb right = lerp(y_ratio, scene->get_background_upper_right(), scene->get_background_lower_right());
        return lerp(x_ratio, right, left);
    }
}

rgb depth_color(Ray ray, Scene* scene, float max_depth, rgb depth_foreground, rgb depth_background) {
    hit_record rec;

    if (scene->hit(ray, 0, std::numeric_limits<float>::max(), rec)) {
        float length = (rec.p - ray.get_origin()).length();
        if(length > max_depth) {
            length = max_depth;
        }
        //colors the spheres with linear interpolation of their distances from the camera
        return length/max_depth * (depth_background - depth_foreground) + depth_background;
    }
    else {
        return depth_background;
    }
}

int main(int argc, char *argv[]) {
    Scene* scene = new Scene();
    Image* image = new Image();
    Camera* camera = new Camera();

    init(scene, image, camera);

    char *buffer = new char[image->get_width() * image->get_height() * 3];
    int pixel_index = 0;
    
    //create a ray for each pixel and with the ray calculate the pixel's color
    for (int row = image->get_height()-1; row >= 0; row--) {
    	for (int col = 0; col < image->get_width(); col++) {
            auto u = float(col)/(image->get_width()-1);
            auto v = float(row)/(image->get_height()-1);
            point3 end_point = camera->get_lower_left_corner() + u * camera->get_horizontal() + v * camera->get_vertical();
            Ray ray(camera->get_origin(), end_point - camera->get_origin());
            rgb c = depth_color(ray, scene, 1.5, rgb(0, 0, 0), rgb(1, 1, 1));
            for (int i = 0; i < 3; i++) {
                buffer[pixel_index] = char(int(255.99 * c[i]));
                pixel_index++;
            }
    	}
    }

    write_file(image, buffer);

    delete scene;
    delete image;
    delete camera;
    delete[] buffer;

	return 0;
}