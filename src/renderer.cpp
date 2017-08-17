#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

#include "../utility/scene.h"
#include "../utility/sphere.h"

//parses input line for information (except colors)
std::string getInfo(std::string line) {
	int start, end;
   	start = line.find_first_of("=") + 2;
    if (line.find_first_of(" ", start) == std::string::npos) {
    	end = line.size();
    }
   	else {
   		end = line.find_first_of(" ", start);
    }
   	return line.substr(start, end-start);
}

//parses input line for color information
vec3 getVector(std::string line) {
    float X, Y, Z;
	int start, end;
   	start = line.find_first_of("=") + 2;
    end = line.find_first_of(" ", start);
    X = std::stoi(line.substr(start, end-start), nullptr);
    start = end+1;
    end = line.find_first_of(" ", start);
    Y = std::stoi(line.substr(start, end-start), nullptr);
    start = end+1;
    if (line.find_first_of(" ", start) == std::string::npos) {
    	end = line.size();
    }
   	else {
   		end = line.find_first_of(" ", start);
    }
   	Z = std::stoi(line.substr(start, end-start), nullptr);
   	return vec3(X, Y, Z);
}

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
	int width, height;
	rgb upper_left, lower_left, upper_right, lower_right;

	//read scene file
	std::string line;
	std::ifstream scene_file (argv[1]);
	if (scene_file.is_open()) {
		getline(scene_file, line);
		name = "images/" + getInfo(line);
    	getline(scene_file, line);
		type = getInfo(line);
		getline(scene_file, line);
		codification = getInfo(line);
		getline(scene_file, line);
		width = std::stoi(getInfo(line), nullptr);
		getline(scene_file, line);
		height = std::stoi(getInfo(line), nullptr);
		getline(scene_file, line);
		upper_left = getVector(line);
		getline(scene_file, line);
		lower_left = getVector(line);
		getline(scene_file, line);
		upper_right = getVector(line);
		getline(scene_file, line);
		lower_right = getVector(line);

    	scene_file.close();
    }
    else {
        name = "images/background2.ppm";
        width = 2000;
        height = 1000;
        codification = "binary";
    }

    char *buffer = new char[width*height*3];
    int k = 0;

    point3 lower_left_corner(-2, -1, -1); // lower left corner of the view plane.
    vec3 horizontal(4, 0, 0); // Horizontal dimension of the view plane.
    vec3 vertical(0, 2, 0); // Vertical dimension of the view plane.
    point3 origin(0, 0, 0); // the camera's origin.

    //create scene with hitables
    Scene* scene = new Scene();
    scene->add_hitable(new Sphere(point3( 0, 0, -1 ), 0.5));
    //scene->add_hitable(new Sphere(point3( 1, 0, -1.5 ), 0.5));
    scene->add_hitable(new Sphere(point3( 0.5, 0, -1.4 ), 0.5));
    //scene->add_hitable(new Sphere(point3( -1.2, 0, -1.3 ), 0.5));
    scene->add_hitable(new Sphere(point3( -0.3, 0, -0.6 ), 0.4));
    scene->add_hitable(new Sphere(point3( 0, -100.5, -1 ), 100));

    //calculating each pixel's rgb with bilinear interpolation
    for (int row = height-1; row >= 0; row--) {
    	for (int col = 0; col < width; col++) {
            auto u = float(col)/(width-1);
            auto v = float(row)/(height-1);
            point3 end_point = lower_left_corner + u*horizontal + v*vertical;
            Ray ray(origin, end_point - origin);
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
    		image_file << width << " " << height << "\n";
    		image_file << "255\n";
    		image_file.write(buffer, width*height*3);
    	}
    	else {
			image_file << "P3\n";
    		image_file << width << " " << height << "\n";
    		image_file << "255\n";
    		for (int i = 0; i < width*height*3; i+=3) {
    			image_file << int((unsigned char )buffer[i]) << " " 
                                << int((unsigned char )buffer[i+1]) << " " 
                                << int((unsigned char )buffer[i+2]) << "\n";
    		}
    	}

    	image_file.close();
  	}

    delete[] buffer;

	return 0;
}