#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <memory>

#include "../include/sphere.h"
#include "../include/diffuse.h"
#include "../include/normal2rgb.h"
#include "../include/depth_map.h"
#include "../include/renderer.h"
#include "../include/recursive.h"


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
    Scene scene;
    Image image(800, 400);
    Camera camera(point3(-2, -1, -1), vec3(4, 0, 0), vec3(0, 2, 0), point3(0, 0, 0));
    Recursive recursive(3);
    Normal2RGB normal2rgb;
    Depth_map depth_map(2.5, rgb(1,1,1), rgb(0,0,0));

    //add background and spheres to the scene
    //scene.set_background(rgb(1, 0.35, 0.35), rgb(1, 0.35, 0.35), rgb(1, 1, 1), rgb(1, 1, 1));
    scene.set_background(rgb(0.5, 0.7, 1), rgb(0.5, 0.7, 1), rgb(1, 1, 1), rgb(1, 1, 1));
    scene.add_hitable(new Sphere(point3( 0, 0, -1 ), 0.5, std::make_shared<Diffuse>(rgb(1,0,0))));
    scene.add_hitable(new Sphere(point3( 0, -100.5, -1 ), 100, std::make_shared<Diffuse>(rgb(0,1,0))));
    scene.add_hitable(new Sphere(point3( 0.5, 0, -1.4 ), 0.5, std::make_shared<Diffuse>(rgb(0,0,1))));
    scene.add_hitable(new Sphere(point3( -0.3, 0, -0.6 ), 0.4, std::make_shared<Diffuse>(rgb(0.5,0,0.5))));

    //scene.add_hitable(new Sphere(point3( 1, 0, -1.5 ), 0.5));
    //scene.add_hitable(new Sphere(point3( -1.2, 0, -1.3 ), 0.5));

    //scene.add_hitable(new Sphere(point3( 0, -100.5, -3 ), 99, rgb(0,1,0)));
    //scene.add_hitable(new Sphere(point3( 0.3, 0, -1 ), 0.4, rgb(1,0,0)));
    //scene.add_hitable(new Sphere(point3( 0, 1, -2 ), 0.6, rgb(0,0,1)));
    //scene.add_hitable(new Sphere(point3( -0.4, 0, -3 ), 0.7, rgb(0.3,0.5,0.6)));

    //add image information
    image.set_mode("recursive");
    image.set_codification("binary");
    if(image.get_mode().compare("normal") == 0)
        image.set_name("images/normal_spheres.ppm");
    else if(image.get_mode().compare("recursive") == 0)
        image.set_name("images/recursive_spheres.ppm");
    else
        image.set_name("images/depth_spheres.ppm");

    char *buffer = new char[image.get_width() * image.get_height() * 3];

    int samples = 32;
    Renderer renderer(scene, image, camera, samples);

    renderer.render(buffer, recursive);

    write_file(image, buffer);

    delete[] buffer;

	return 0;
}