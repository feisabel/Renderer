#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <memory>
#include <chrono>

#include "../include/sphere.h"
#include "../include/diffuse.h"
#include "../include/bp_material.h"
#include "../include/normal2rgb.h"
#include "../include/depth_map.h"
#include "../include/renderer.h"
#include "../include/recursive.h"
#include "../include/blinn_phong.h"
#include "../include/metal.h"


void write_file(Image& image, char* buffer) {
    std::ofstream image_file (image.get_name());
    if (image_file.is_open()) {
        if (image.get_codification().compare("binary") == 0) {
            image_file << "P6\n";
            image_file << image.get_width() << " " << image.get_height() << "\n";
            image_file << "255\n";
            image_file.write(buffer, image.get_width() * image.get_height() * 3);
        }
        else {
            image_file << "P3\n";
            image_file << image.get_width() << " " << image.get_height() << "\n";
            image_file << "255\n";
            for (int i = 0; i < image.get_width() * image.get_height() * 3; i+=3) {
                image_file << int((unsigned char )buffer[i]) << " " 
                                << int((unsigned char )buffer[i+1]) << " " 
                                << int((unsigned char )buffer[i+2]) << "\n";
            }
        }

        image_file.close();
    }
}

int main(int argc, char *argv[]) {
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    Scene scene;
    Image image(400, 200);
    Camera camera(point3(-2, -1, -1), vec3(4, 0, 0), vec3(0, 2, 0), point3(0, 0, 0));

    //shaders
    Recursive recursive(3);
    Normal2RGB normal2rgb;
    Depth_map depth_map(2.5, rgb(1,1,1), rgb(0,0,0));
    Blinn_phong blinn_phong;

    blinn_phong.set_shadow(true);

    //add lights
    scene.add_light(std::make_shared<Light>(vec3(7,-8,-0), rgb(0.8,0.8,0.8), rgb(0.8,0.8,0.8)));
    scene.add_light(std::make_shared<Light>(vec3(-20,-10,-15), rgb(0.5,0.5,0.5), rgb(0.5,0.5,0.5)));
    scene.add_ambient_light(rgb(0.4,0.4,0.4));

    //add background and spheres to the scene
    //scene.set_background(rgb(1, 0.35, 0.35), rgb(1, 0.35, 0.35), rgb(1, 1, 1), rgb(1, 1, 1));
    scene.set_background(rgb(0.5, 0.7, 1), rgb(0.5, 0.7, 1), rgb(1, 1, 1), rgb(1, 1, 1));
    //scene.add_hitable(std::make_shared<Sphere>(point3( 0, 0, -1 ), 0.5, std::make_shared<Diffuse>(rgb(1,0,0))));
    //scene.add_hitable(std::make_shared<Sphere>(point3( 0, -100.5, -1 ), 100, std::make_shared<Diffuse>(rgb(0,1,0))));
    //scene.add_hitable(std::make_shared<Sphere>(point3( 0.5, 0, -1.4 ), 0.5, std::make_shared<Diffuse>(rgb(0,0,1))));
    //scene.add_hitable(std::make_shared<Sphere>(point3( -0.3, 0, -0.6 ), 0.4, std::make_shared<Diffuse>(rgb(0.5,0,0.5))));

    //scene.add_hitable(new Sphere(point3( 1, 0, -1.5 ), 0.5));
    //scene.add_hitable(new Sphere(point3( -1.2, 0, -1.3 ), 0.5));

    //specular, ambient, diffuse
    /*scene.add_hitable(std::make_shared<Sphere>(point3( 0, -100.4, -1 ), 100, 
        std::make_shared<BP_material>(rgb(0.3,0.3,0.3), rgb(0.1,0.1,0.1), rgb(0,1,0), 1)));

    scene.add_hitable(std::make_shared<Sphere>(point3( 0, 0.01, -1 ), 0.4, 
        std::make_shared<BP_material>(rgb(1,1,1), rgb(0.1,0.1,0.1), rgb(1,0,0), 8)));
    scene.add_hitable(std::make_shared<Sphere>(point3( 0.01, 0.016, -0.949 ), 0.35, 
        std::make_shared<BP_material>(rgb(1,1,1), rgb(0.1,0.1,0.1), rgb(1,1,1), 8)));

    scene.add_hitable(std::make_shared<Sphere>(point3( -0.81, 0.01, -1 ), 0.4, 
        std::make_shared<BP_material>(rgb(1,1,1), rgb(0.1,0.1,0.1), rgb(0,0,1), 8)));
    scene.add_hitable(std::make_shared<Sphere>(point3( -0.81, 0.03, -0.952 ), 0.35, 
        std::make_shared<BP_material>(rgb(1,1,1), rgb(0.1,0.1,0.1), rgb(1,1,1), 8)));

    scene.add_hitable(std::make_shared<Sphere>(point3( 0.9, 0.01, -1 ), 0.4, 
        std::make_shared<BP_material>(rgb(1,1,1), rgb(0.1,0.1,0.1), rgb(1,1,0), 8)));
    scene.add_hitable(std::make_shared<Sphere>(point3( 0.9, -0.01, -0.952 ), 0.35, 
        std::make_shared<BP_material>(rgb(1,1,1), rgb(0.1,0.1,0.1), rgb(1,1,1), 8)));

    scene.add_hitable(std::make_shared<Sphere>(point3( 0, -100.5, -1 ), 100, 
        std::make_shared<BP_material>(rgb(0,0,0), rgb(0.1,0.1,0.1), rgb(0.8,0.8,0.8), 64)));
    scene.add_hitable(std::make_shared<Sphere>(point3( 0, 0, -1 ), 0.5, 
        std::make_shared<BP_material>(rgb(1,1,1), rgb(0.1,0.1,0.1), rgb(0.7,0.2,0.1), 64)));*/

    //scene.add_hitable(new Sphere(point3( 0.3, 0, -1 ), 0.4, rgb(1,0,0)));
    //scene.add_hitable(new Sphere(point3( 0, 1, -2 ), 0.6, rgb(0,0,1)));
    //scene.add_hitable(new Sphere(point3( -0.4, 0, -3 ), 0.7, rgb(0.3,0.5,0.6)));

    scene.add_hitable(std::make_shared<Sphere>(point3(0,0,-1), 0.5, std::make_shared<Diffuse>(rgb(0.8,0.3,0.3))));
    scene.add_hitable(std::make_shared<Sphere>(point3(0,-100.5,-1), 100, std::make_shared<Diffuse>(rgb(0.8,0.8,0))));
    scene.add_hitable(std::make_shared<Sphere>(point3(1,0,-1), 0.5, std::make_shared<Metal>(rgb(0.8,0.6,0.2), 1)));
    scene.add_hitable(std::make_shared<Sphere>(point3(-1,0,-1), 0.5, std::make_shared<Metal>(rgb(0.8,0.8,0.8), 0.3)));

    //add image information
    image.set_mode("blinnphong");
    image.set_codification("binary");
    if(image.get_mode().compare("normal") == 0)
        image.set_name("images/normal_spheres.ppm");
    else if(image.get_mode().compare("recursive") == 0)
        image.set_name("images/recursive_spheres.ppm");
    else if(image.get_mode().compare("blinnphong") == 0)
        image.set_name("images/blinnphong_spheres.ppm");
    else
        image.set_name("images/depth_spheres.ppm");

    char *buffer = new char[image.get_width() * image.get_height() * 3];

    //number of rays per pixel
    int samples = 32;
    Renderer renderer(scene, image, camera, samples);

    renderer.render(buffer, recursive);

    write_file(image, buffer);

    delete[] buffer;

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::seconds>( t2 - t1 ).count() << std::endl;
	return 0;
}