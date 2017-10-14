#include "../include/parser.h"

void parse_input(std::string folder, Scene& scene, Image& image, Camera& camera, std::unique_ptr<Shader>& shader) {
    parse_background(folder, scene);
    parse_camera(folder, camera);
    parse_image(folder, image);
    parse_shader(folder, shader);
    parse_spheres(folder, scene);
    parse_lights(folder, scene);
}

void parse_background(std::string folder, Scene& scene) {
	std::ifstream background_file ("data/"+folder+"/background.txt");
    if (background_file.is_open()) {
    	std::string s;

    	background_file >> s;
    	getline(background_file, s, ' ');
    	getline(background_file, s);
    	scene.set_background_upper_left(parse_vector(s));
    	background_file >> s;
    	getline(background_file, s, ' ');
    	getline(background_file, s);
    	scene.set_background_upper_right(parse_vector(s));
    	background_file >> s;
    	getline(background_file, s, ' ');
    	getline(background_file, s);
    	scene.set_background_lower_left(parse_vector(s));
    	background_file >> s;
    	getline(background_file, s, ' ');
    	getline(background_file, s);
    	scene.set_background_lower_right(parse_vector(s));

    	background_file.close();
    }
    else {
    	std::cout << "Error opening background file." << std::endl;
    }
}

void parse_camera(std::string folder, Camera& camera) {
	std::ifstream camera_file ("data/"+folder+"/camera.txt");
	if (camera_file.is_open()) {
		std::string s;

    	camera_file >> s;
    	getline(camera_file, s, ' ');
    	getline(camera_file, s);
    	camera.set_position(parse_vector(s));
    	camera_file >> s;
    	getline(camera_file, s, ' ');
    	getline(camera_file, s);
    	camera.set_lower_left_corner(parse_vector(s));
    	camera_file >> s;
    	getline(camera_file, s, ' ');
    	getline(camera_file, s);
    	camera.set_horizontal(parse_vector(s));
    	camera_file >> s;
    	getline(camera_file, s, ' ');
    	getline(camera_file, s);
    	camera.set_vertical(parse_vector(s));

		camera_file.close();
	}
	else {
    	std::cout << "Error opening camera file." << std::endl;
    }
}

void parse_image(std::string folder, Image& image) {
	std::ifstream image_file ("data/"+folder+"/image.txt");
    if (image_file.is_open()) {
    	std::string s;

    	image_file >> s;
    	getline(image_file, s, ' ');
    	getline(image_file, s);
    	image.set_width(stoi(s));
    	image_file >> s;
    	getline(image_file, s, ' ');
    	getline(image_file, s);
    	image.set_height(stoi(s));
    	image_file >> s;
    	getline(image_file, s, ' ');
    	getline(image_file, s);
    	image.set_codification(s);
    	image_file >> s;
    	getline(image_file, s, ' ');
    	getline(image_file, s);
    	image.set_samples(stoi(s));
    	image.set_name("images/"+folder+".ppm");

    	image_file.close();
    }
    else {
    	std::cout << "Error opening image file." << std::endl;
    }
}

void parse_shader(std::string folder, std::unique_ptr<Shader>& shader) {
	std::ifstream shader_file ("data/"+folder+"/shader.txt");
    if (shader_file.is_open()) {
    	std::string s;

    	shader_file >> s;
    	getline(shader_file, s, ' ');
    	getline(shader_file, s);

	    if(s.compare("recursive") == 0) {
	    	shader_file >> s;
    		getline(shader_file, s, ' ');
    		getline(shader_file, s);
    		int recursions = stoi(s);
	    	shader = std::unique_ptr<Recursive>(new Recursive(recursions));
    	}
    	else if(s.compare("blinnphong") == 0) {
    		shader_file >> s;
    		getline(shader_file, s, ' ');
    		getline(shader_file, s);
    		bool shadow;
    		if(s.compare("yes") == 0)
    			shadow = true;
    		else
    			shadow = false;
    		shader = std::unique_ptr<Blinn_phong>(new Blinn_phong(shadow));
    	}
    	else if(s.compare("normal2rgb") == 0) {
    		shader = std::unique_ptr<Normal2RGB>(new Normal2RGB);
    	}
    	else if(s.compare("depthmap") == 0) {
    		shader_file >> s;
    		getline(shader_file, s, ' ');
    		getline(shader_file, s);
    		double max_depth = stod(s);
    		shader_file >> s;
    		getline(shader_file, s, ' ');
    		getline(shader_file, s);
    		rgb background = parse_vector(s);
    		shader_file >> s;
    		getline(shader_file, s, ' ');
    		getline(shader_file, s);
    		rgb foreground = parse_vector(s);

    		shader = std::unique_ptr<Depth_map>(new Depth_map(max_depth,background,foreground));
    	}
        else if(s.compare("cartoon") == 0) {
            shader = std::unique_ptr<Cartoon>(new Cartoon);
        }
    }
    else {
    	std::cout << "Error opening shader file." << std::endl;
    }
}

void parse_spheres(std::string folder, Scene& scene) {
	std::ifstream spheres_file ("data/"+folder+"/spheres.txt");
    if (spheres_file.is_open()) {
    	std::string s;
    	
    	while(spheres_file >> s) {
    		getline(spheres_file, s, ' ');
    		getline(spheres_file, s);
    		point3 center = parse_vector(s);
    		spheres_file >> s;
    		getline(spheres_file, s, ' ');
    		getline(spheres_file, s);
    		double radius = stod(s);
    		spheres_file >> s;
    		getline(spheres_file, s, ' ');
    		getline(spheres_file, s);
    		if(s.compare("metal") == 0) {
    			spheres_file >> s;
    			getline(spheres_file, s, ' ');
    			getline(spheres_file, s);
    			rgb albedo = parse_vector(s);
    			spheres_file >> s;
    			getline(spheres_file, s, ' ');
    			getline(spheres_file, s);
    			double fuzzyness = stod(s);
    			scene.add_hitable(std::make_shared<Sphere>(center, radius, std::make_shared<Metal>(albedo, fuzzyness)));
    		}
    		else if(s.compare("diffuse") == 0) { 
    			spheres_file >> s;
    			getline(spheres_file, s, ' ');
    			getline(spheres_file, s);
    			rgb albedo = parse_vector(s);
    			scene.add_hitable(std::make_shared<Sphere>(center, radius, std::make_shared<Diffuse>(albedo)));
    		}
            else if(s.compare("bp") == 0) { 
                spheres_file >> s;
                getline(spheres_file, s, ' ');
                getline(spheres_file, s);
                rgb ka = parse_vector(s);
                spheres_file >> s;
                getline(spheres_file, s, ' ');
                getline(spheres_file, s);
                rgb kd = parse_vector(s);
                spheres_file >> s;
                getline(spheres_file, s, ' ');
                getline(spheres_file, s);
                rgb ks = parse_vector(s);
                spheres_file >> s;
                getline(spheres_file, s, ' ');
                getline(spheres_file, s);
                double alpha = stod(s);
                scene.add_hitable(std::make_shared<Sphere>(center, radius, std::make_shared<BP_material>(ka, kd, ks, alpha)));
            }
            else if(s.compare("gradient") == 0) {
                spheres_file >> s;
                getline(spheres_file, s, ' ');
                getline(spheres_file, s);
                int n = stoi(s);
                spheres_file >> s;
                getline(spheres_file, s, ' ');
                getline(spheres_file, s);
                rgb outline_color = parse_vector(s);
                spheres_file >> s;
                getline(spheres_file, s, ' ');
                getline(spheres_file, s);
                rgb shadow_color = parse_vector(s);
                spheres_file >> s;
                std::vector<rgb> colors;
                for(int i = 0; i < n; i++) {
                    getline(spheres_file, s, ' ');
                    getline(spheres_file, s, ')');
                    s += ")";
                    colors.push_back(parse_vector(s));
                } 
                spheres_file >> s;
                std::vector<double> partitions;
                getline(spheres_file, s, ' ');
                for(int i = 0; i < n-1; i++) {
                    getline(spheres_file, s, ' ');
                    partitions.push_back(stod(s));
                }
                getline(spheres_file, s);
                partitions.push_back(stod(s));
                scene.add_hitable(std::make_shared<Sphere>(center, radius, std::make_shared<Gradient>(n, outline_color, shadow_color, colors, partitions))); 
            }
    	}

    	spheres_file.close();
    }
    else {
    	std::cout << "Error opening spheres file." << std::endl;
    }
}

void parse_lights(std::string folder, Scene& scene) {
	std::ifstream lights_file ("data/"+folder+"/lights.txt");
    if (lights_file.is_open()) {
    	std::string s;

    	lights_file >> s;
    	getline(lights_file, s, ' ');
    	getline(lights_file, s);
    	scene.add_ambient_light(parse_vector(s));

    	while(lights_file >> s) {
            getline(lights_file, s, ' ');
            getline(lights_file, s);
            if(s.compare("direction") == 0) {
        		getline(lights_file, s, ' ');
        		getline(lights_file, s);
        		vec3 direction = parse_vector(s);
        		lights_file >> s;
        		getline(lights_file, s, ' ');
        		getline(lights_file, s);
        		rgb diffuse_intensity = parse_vector(s);
        		lights_file >> s;
        		getline(lights_file, s, ' ');
        		getline(lights_file, s);
        		rgb specular_intensity = parse_vector(s);
        		scene.add_light(std::make_shared<Direction_light>(direction, diffuse_intensity, specular_intensity));
            }
            if(s.compare("point") == 0) {
                getline(lights_file, s, ' ');
                getline(lights_file, s);
                point3 position = parse_vector(s);
                lights_file >> s;
                getline(lights_file, s, ' ');
                getline(lights_file, s);
                rgb diffuse_intensity = parse_vector(s);
                lights_file >> s;
                getline(lights_file, s, ' ');
                getline(lights_file, s);
                rgb specular_intensity = parse_vector(s);
                scene.add_light(std::make_shared<Point_light>(position, diffuse_intensity, specular_intensity));
            }
            if(s.compare("spotlight") == 0) {
                getline(lights_file, s, ' ');
                getline(lights_file, s);
                point3 position = parse_vector(s);
                lights_file >> s;
                getline(lights_file, s, ' ');
                getline(lights_file, s);
                vec3 direction = parse_vector(s);
                lights_file >> s;
                getline(lights_file, s, ' ');
                getline(lights_file, s);
                double angle = stod(s);
                lights_file >> s;
                getline(lights_file, s, ' ');
                getline(lights_file, s);
                rgb diffuse_intensity = parse_vector(s);
                lights_file >> s;
                getline(lights_file, s, ' ');
                getline(lights_file, s);
                rgb specular_intensity = parse_vector(s);
                scene.add_light(std::make_shared<Spotlight>(position, direction, angle, diffuse_intensity, specular_intensity));
            }
    	}

    	lights_file.close();
    }
    else {
    	std::cout << "Error opening lights file." << std::endl;
    }
}

vec3 parse_vector(std::string v) {
	std::stringstream ss(v);
	std::string s;
	double x, y, z;
	getline(ss, s, '(');
	getline(ss, s, ',');
	x = stod(s);
	getline(ss, s, ' ');
	getline(ss, s, ',');
	y = stod(s);
	getline(ss, s, ' ');
	getline(ss, s, ')');
	z = stod(s);
	return vec3(x,y,z);
}