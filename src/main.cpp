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
#include "../include/parser.h"

void write_file(Image& image, char* buffer) {
    std::ofstream output_file (image.get_name());
    if (output_file.is_open()) {
        if (image.get_codification().compare("binary") == 0) {
            output_file << "P6\n";
            output_file << image.get_width() << " " << image.get_height() << "\n";
            output_file << "255\n";
            output_file.write(buffer, image.get_width() * image.get_height() * 3);
        }
        else {
            output_file << "P3\n";
            output_file << image.get_width() << " " << image.get_height() << "\n";
            output_file << "255\n";
            for (int i = 0; i < image.get_width() * image.get_height() * 3; i+=3) {
                output_file << int((unsigned char )buffer[i]) << " " 
                                << int((unsigned char )buffer[i+1]) << " " 
                                << int((unsigned char )buffer[i+2]) << "\n";
            }
        }

        output_file.close();
    }
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cout << "Invalid number of arguments" << std::endl;
        return 0;
    }

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    Scene scene;
    Image image;
    Camera camera;
    std::unique_ptr<Shader> shader;

    parse_input(argv[1], scene, image, camera, shader);
   
    char *buffer = new char[image.get_width() * image.get_height() * 3];

    Renderer renderer(scene, image, camera);

    renderer.render(buffer, shader);

    write_file(image, buffer);

    delete[] buffer;

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::seconds>( t2 - t1 ).count() << " seconds elapsed" << std::endl;
	return 0;
}