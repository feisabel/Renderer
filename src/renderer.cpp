#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

#include "../utility/scene.h"
#include "../utility/sphere.h"
#include "../utility/camera.h"
#include "../utility/image.h"


rgb color(Ray ray, Scene* scene) {
    hit_record rec;

    if (scene->hit(ray, 0, std::numeric_limits<float>::max(), rec)) {
        return (rec.normal + vec3(1, 1, 1))/2;
    }
    else {
        rgb upper_left(0.5, 0.7, 1);
        rgb upper_right(0.5, 0.7, 1);
        rgb lower_left(1, 1, 1);
        rgb lower_right(1, 1, 1);

        vec3 unit_ray = unit_vector(ray.get_direction());
        float x_ratio = unit_ray.x();
        x_ratio += 1;
        x_ratio /= 2;
        float y_ratio = unit_ray.y();
        y_ratio += 1;
        y_ratio /= 2;

        rgb left = y_ratio * (upper_left - lower_left) + lower_left;
        rgb right = y_ratio * (upper_right - lower_right) + lower_right;
        return x_ratio * (right - left) + right;
    }
}

int main(int argc, char *argv[]) {
	std::string name, type, codification;

    name = "images/background2.ppm";
    codification = "binary";

    Image* image = new Image(2000, 1000);
    Camera* camera = new Camera(point3(-2, -1, -1), vec3(4, 0, 0), vec3(0, 2, 0), point3(0, 0, 0));

    char *buffer = new char[image->get_width() * image->get_height() * 3];
    int k = 0;

    //create scene with hitables
    Scene* scene = new Scene();
    scene->add_hitable(new Sphere(point3( 0, 0, -1 ), 0.5));
    scene->add_hitable(new Sphere(point3( 0, -100.5, -1 ), 100));

    scene->add_hitable(new Sphere(point3( 0.5, 0, -1.4 ), 0.5));
    scene->add_hitable(new Sphere(point3( -0.3, 0, -0.6 ), 0.4));

    //scene->add_hitable(new Sphere(point3( 1, 0, -1.5 ), 0.5));
    //scene->add_hitable(new Sphere(point3( -1.2, 0, -1.3 ), 0.5));

    //calculating each pixel's rgb with bilinear interpolation
    for (int row = image->get_height()-1; row >= 0; row--) {
    	for (int col = 0; col < image->get_width(); col++) {
            auto u = float(col)/(image->get_width()-1);
            auto v = float(row)/(image->get_height()-1);
            point3 end_point = camera->get_lower_left_corner() + u * camera->get_horizontal() + v * camera->get_vertical();
            Ray ray(camera->get_origin(), end_point - camera->get_origin());
            rgb c = color(ray, scene);
            for (int i = 0; i < 3; i++) {
                buffer[k] = char(int(255.99 * c[i]));
                k++;
            }
    	}
    }

    //writing image file
    std::ofstream image_file (name);
  	if (image_file.is_open()) {
    	if (codification.compare("binary") == 0) {
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

    delete scene;
    delete image;
    delete camera;
    delete[] buffer;

	return 0;
}