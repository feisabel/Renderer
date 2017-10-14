#ifndef _PARSER_H_
#define _PARSER_H_

#include "../include/scene.h"
#include "../include/camera.h"
#include "../include/image.h"
#include "../include/blinn_phong.h"
#include "../include/depth_map.h"
#include "../include/recursive.h"
#include "../include/normal2rgb.h"
#include "../include/cartoon.h"
#include "../include/sphere.h"
#include "../include/diffuse.h"
#include "../include/metal.h"
#include "../include/bp_material.h"
#include "../include/direction_light.h"
#include "../include/point_light.h"
#include "../include/spotlight.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <memory>

vec3 parse_vector(std::string v);
void parse_background(std::string folder, Scene& scene);
void parse_camera(std::string folder, Camera& camera);
void parse_image(std::string folder, Image& image);
void parse_shader(std::string folder, std::unique_ptr<Shader>& shader);
void parse_spheres(std::string folder, Scene& scene);
void parse_lights(std::string folder, Scene& scene);
void parse_input(std::string folder, Scene& scene, Image& image, Camera& camera, std::unique_ptr<Shader>& shader);

#endif