#include "../include/renderer.h"
#include <iostream> 

void Renderer::render(char* buffer, std::unique_ptr<Shader>& shader) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int pixel_index = 0;
    //create rays for each pixel and with each ray calculate the pixel's color
    for (int row = image.get_height()-1; row >= 0; row--) {
        if(row > 0)
            std::cout << "\r" << int((1.0 - double(row)/(image.get_height()-1))*100.0) << "%" << std::flush;
        for (int col = 0; col < image.get_width(); col++) {
            rgb c(0,0,0);
            //anti-aliasing loop
            for(int k = 0; k < image.get_samples(); k ++) {
                auto u = (double(col) + std::generate_canonical<double,10>(gen)) / (image.get_width()-1);
                auto v = (double(row) + std::generate_canonical<double,10>(gen)) / (image.get_height()-1);
                Ray ray = camera.get_ray(u, v);
                c += shader->color(ray, scene);;
            }
            c /= image.get_samples();
            //correct gamma
            c = rgb(sqrt(c[0]), sqrt(c[1]), sqrt(c[2]));
            for (int i = 0; i < 3; i++) {
                buffer[pixel_index] = char(int(255.99 * c[i]));
                pixel_index++;
            }
        }
    }
    std::cout << "\r" << 100 << "%" << std::endl; 
}
