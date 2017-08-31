#include "../include/renderer.h"
#include <iostream> 

void Renderer::render(char* buffer, Shader& shader) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int pixel_index = 0;
    //create a ray for each pixel and with the ray calculate the pixel's color
    for (int row = image.get_height()-1; row >= 0; row--) {
        if(row > 0)
            std::cout << "\r" << int((1.0 - float(row)/(image.get_height()-1))*100.0) << "%" << std::flush;
        for (int col = 0; col < image.get_width(); col++) {
            rgb c(0,0,0);
            for(int k = 0; k < samples; k ++) {
                auto u = (float(col) + std::generate_canonical<float,10>(gen)) / (image.get_width()-1);
                auto v = (float(row) + std::generate_canonical<float,10>(gen)) / (image.get_height()-1);
                point3 end_point = camera.get_lower_left_corner() + u * camera.get_horizontal() + v * camera.get_vertical();
                Ray ray(camera.get_origin(), end_point - camera.get_origin());
                c += shader.color(ray, scene);
            }
            c /= samples;
            c = rgb(sqrt(c[0]), sqrt(c[1]), sqrt(c[2]));
            for (int i = 0; i < 3; i++) {
                buffer[pixel_index] = char(int(255.99 * c[i]));
                pixel_index++;
            }
        }
    }
    std::cout << "\r" << 100 << "%" << std::endl;
}
