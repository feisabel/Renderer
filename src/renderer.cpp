#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

#include "../utility/scene.h"
#include "../utility/sphere.h"
#include "../utility/camera.h"
#include "../utility/image.h"

void init(Scene* scene, Image* image, Camera* camera) {
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

    image->set_dimensions(2000, 1000);
    image->set_name("images/normal_spheres.ppm");
    image->set_codification("binary");

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

rgb color(Ray ray, Scene* scene) {
    hit_record rec;

    if (scene->hit(ray, 0, std::numeric_limits<float>::max(), rec)) {
        return (rec.normal + vec3(1, 1, 1))/2;
    }
    else {
        vec3 unit_ray = unit_vector(ray.get_direction());
        float x_ratio = (unit_ray.x()+1.0)/2.0;
        float y_ratio = (unit_ray.y()+1.0)/2.0;

        rgb left = lerp(y_ratio, scene->get_background_upper_left(), scene->get_background_lower_left());
        rgb right = lerp(y_ratio, scene->get_background_upper_right(), scene->get_background_lower_right());
        return lerp(x_ratio, right, left);
    }
}

int main(int argc, char *argv[]) {
    Scene* scene = new Scene();
    Image* image = new Image();
    Camera* camera = new Camera();

    init(scene, image, camera);

    char *buffer = new char[image->get_width() * image->get_height() * 3];
    int pixel_index = 0;
    
    // calculate each pixel's rgb with bilinear interpolation
    for (int row = image->get_height()-1; row >= 0; row--) {
    	for (int col = 0; col < image->get_width(); col++) {
            auto u = float(col)/(image->get_width()-1);
            auto v = float(row)/(image->get_height()-1);
            point3 end_point = camera->get_lower_left_corner() + u * camera->get_horizontal() + v * camera->get_vertical();
            Ray ray(camera->get_origin(), end_point - camera->get_origin());
            rgb c = color(ray, scene);
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