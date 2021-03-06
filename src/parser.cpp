#include "../include/parser.h"
#include "../include/OBJ_Loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

void parse_input(std::string folder, Scene& scene, Image& image, Camera& camera, std::unique_ptr<Shader>& shader) {
    parse_background(folder, scene);
    parse_camera(folder, camera);
    parse_image(folder, image);
    parse_shader(folder, shader);
    parse_hitables(folder, scene);
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
    	point3 look_from = parse_vector(s);
    	camera_file >> s;
    	getline(camera_file, s, ' ');
    	getline(camera_file, s);
    	point3 look_at = parse_vector(s);
    	camera_file >> s;
    	getline(camera_file, s, ' ');
    	getline(camera_file, s);
    	vec3 up_vector = parse_vector(s);
    	camera_file >> s;
    	getline(camera_file, s, ' ');
    	getline(camera_file, s);
    	std::string projection = s;
        camera.set_camera(look_from, look_at, up_vector, projection);
        if(s.compare("perspective") == 0) {
            camera_file >> s;
            getline(camera_file, s, ' ');
            getline(camera_file, s);
            double fov = stod(s);
            camera_file >> s;
            getline(camera_file, s, ' ');
            getline(camera_file, s);
            double ratio = stod(s);
            camera_file >> s;
            getline(camera_file, s, ' ');
            getline(camera_file, s);
            double d = stod(s);
            camera_file >> s;
            getline(camera_file, s, ' ');
            getline(camera_file, s);
            double aperture = stod(s);
            std::string s2 = "";
            camera_file >> s2;
            if(s2.size() == 0) {
                camera.set_perspective(fov, ratio, d, aperture);
            }
            else {
                getline(camera_file, s2, ' ');
                getline(camera_file, s2);
                vec3 vpn = parse_vector(s2);
                camera.set_perspective(fov, ratio, d, aperture, vpn);
            }
        }
        else if(s.compare("parallel") == 0) {
            camera_file >> s;
            getline(camera_file, s, ' ');
            getline(camera_file, s);
            double l = stod(s);
            camera_file >> s;
            getline(camera_file, s, ' ');
            getline(camera_file, s);
            double r = stod(s);
            camera_file >> s;
            getline(camera_file, s, ' ');
            getline(camera_file, s);
            double t = stod(s);
            camera_file >> s;
            getline(camera_file, s, ' ');
            getline(camera_file, s);
            double b = stod(s);
            std::string s2 = "";
            camera_file >> s2;
            if(s2.size() == 0) {
                camera.set_parallel(l, r, t, b);
            }
            else {
                getline(camera_file, s2, ' ');
                getline(camera_file, s2);
                vec3 vpn = parse_vector(s2);
                camera.set_parallel(l, r, t, b, vpn);
            }
        }

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

std::shared_ptr<Texture> get_texture(std::ifstream& hitables_file) {
    std::string s;
    hitables_file >> s;
    getline(hitables_file, s, ' ');
    getline(hitables_file, s);
    std::string texture_type = s;
    std::shared_ptr<Texture> texture;
    if(texture_type.compare("solid") == 0) {
        hitables_file >> s;
        getline(hitables_file, s, ' ');
        getline(hitables_file, s);
        rgb albedo = parse_vector(s);
        texture = std::make_shared<Solid_texture>(albedo);
    }
    else if(texture_type.compare("checker") == 0) {
        std::shared_ptr<Texture> texture1 = get_texture(hitables_file);
        std::shared_ptr<Texture> texture2 = get_texture(hitables_file);
        texture = std::make_shared<Checker_texture>(texture1, texture2);
    }
    else if(texture_type.compare("perlin") == 0) {
        hitables_file >> s;
        getline(hitables_file, s, ' ');
        getline(hitables_file, s);
        double scale = stod(s);
        texture = std::make_shared<Perlin_texture>(scale);
    }
    else if(texture_type.compare("image") == 0) {
        hitables_file >> s;
        getline(hitables_file, s, ' ');
        getline(hitables_file, s);
        std::string image_name = "data/textures/" + s;
        int width, height, dummy;
        unsigned char* data = stbi_load(image_name.c_str(), &width, &height, &dummy, 3);
        texture = std::make_shared<Image_texture>(data, width, height);
    }
    return texture;
}

void parse_hitables(std::string folder, Scene& scene) {
	std::ifstream hitables_file ("data/"+folder+"/hitables.txt");
    if (hitables_file.is_open()) {
    	std::string s;
        point3 center, v0, v1, v2, v3, v4, v5, v6, v7;
        double radius;
        std::string mesh_file;
        std::shared_ptr<Hitable> hitable;
        std::shared_ptr<Material> material;
    	
    	while(hitables_file >> s) {
            getline(hitables_file, s, ' ');
            getline(hitables_file, s);
            std::string type = s;
            if(type.compare("sphere") == 0) {
                hitables_file >> s;
        		getline(hitables_file, s, ' ');
        		getline(hitables_file, s);
        		center = parse_vector(s);
        		hitables_file >> s;
        		getline(hitables_file, s, ' ');
        		getline(hitables_file, s);
        		radius = stod(s);
            }
            else if(type.compare("triangle") == 0) {
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                v0 = parse_vector(s);
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                v1 = parse_vector(s);
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                v2 = parse_vector(s);
            }
            else if(type.compare("box") == 0) {
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                v0 = parse_vector(s);
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                v1 = parse_vector(s);
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                v2 = parse_vector(s);
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                v3 = parse_vector(s);
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                v4 = parse_vector(s);
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                v5 = parse_vector(s);
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                v6 = parse_vector(s);
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                v7 = parse_vector(s);
            }
            else if(type.compare("mesh") == 0) {
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                mesh_file = s;
            }
            hitables_file >> s;
            getline(hitables_file, s, ' ');
            getline(hitables_file, s);
            std::string material_type = s;
            if(material_type.compare("dielectric") == 0) {
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                double ref_idx = stod(s);
                material = std::make_shared<Dielectric>(ref_idx);
            }
    		else if(material_type.compare("metal") == 0 || material_type.compare("diffuse") == 0 || material_type.compare("light") == 0) {
                std::shared_ptr<Texture> texture = get_texture(hitables_file);
                if(material_type.compare("metal") == 0) {
        			hitables_file >> s;
        			getline(hitables_file, s, ' ');
        			getline(hitables_file, s);
        			double fuzzyness = stod(s);
                    material = std::make_shared<Metal>(texture, fuzzyness);
                }
                else if(material_type.compare("diffuse") == 0){
                    material = std::make_shared<Diffuse>(texture);
                }
                else if(material_type.compare("light") == 0) {
                    material = std::make_shared<Light_material>(texture);
                }
    		}
            else if(material_type.compare("bp") == 0) { 
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                rgb ka = parse_vector(s);
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                rgb kd = parse_vector(s);
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                rgb ks = parse_vector(s);
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                double alpha = stod(s);
                material = std::make_shared<BP_material>(ka, kd, ks, alpha);
            }
            else if(material_type.compare("gradient") == 0) {
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                int n = stoi(s);
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                rgb outline_color = parse_vector(s);
                hitables_file >> s;
                getline(hitables_file, s, ' ');
                getline(hitables_file, s);
                rgb shadow_color = parse_vector(s);
                hitables_file >> s;
                std::vector<rgb> colors;
                for(int i = 0; i < n; i++) {
                    getline(hitables_file, s, ' ');
                    getline(hitables_file, s, ')');
                    s += ")";
                    colors.push_back(parse_vector(s));
                } 
                hitables_file >> s;
                std::vector<double> partitions;
                getline(hitables_file, s, ' ');
                for(int i = 0; i < n-1; i++) {
                    getline(hitables_file, s, ' ');
                    partitions.push_back(stod(s));
                }
                getline(hitables_file, s);
                partitions.push_back(stod(s));
                material = std::make_shared<Gradient>(n, outline_color, shadow_color, colors, partitions);
            }
            hitables_file >> s;
            getline(hitables_file, s, ' ');
            getline(hitables_file, s);
            int transfs = stoi(s);
            mat4 t;
            for(int i = 0; i < transfs; i++) {
                hitables_file >> s;
                std::string transform_type = s;
                getline(hitables_file, s, ' ');
                mat4 m;
                if(transform_type.compare("translate:") == 0) {
                    getline(hitables_file, s);
                    vec3 v = parse_vector(s);                    
                    m.translate(v);
                }
                else if(transform_type.compare("scale:") == 0) {
                    getline(hitables_file, s);
                    vec3 v = parse_vector(s);
                    m.scale(v);
                }
                else if(transform_type.compare("rotate:") == 0) {
                    getline(hitables_file, s, ' ');
                    double angle = stod(s);
                    getline(hitables_file, s);
                    char c = s[0];
                    vec3 centroid = (v0 + v1 + v2) / 3;
                    mat4 aux1, aux2;
                    centroid = - centroid;
                    aux1.translate(centroid);
                    t *= aux1;
                    aux2.rotate(angle, c);
                    t *= aux2;
                    centroid = - centroid;
                    m.translate(centroid);
                }
                t *= m;
            }
            if(type.compare("sphere") == 0) {
                hitable = std::make_shared<Sphere>(center, radius, material);
                if(transfs > 0) {
                    hitable->transform(t);
                }
                scene.add_hitable(hitable);
            }
            else if(type.compare("triangle")==0) {
                hitable = std::make_shared<Triangle>(v0, v1, v2, material);
                if(transfs > 0) {
                    hitable->transform(t);
                }
                scene.add_hitable(hitable);
            }
            else if(type.compare("box") == 0) {
                scene.add_hitable(std::make_shared<Triangle>(v0, v1, v2, material));
                scene.add_hitable(std::make_shared<Triangle>(v0, v2, v3, material));
                scene.add_hitable(std::make_shared<Triangle>(v4, v5, v6, material));
                scene.add_hitable(std::make_shared<Triangle>(v4, v6, v7, material));
                scene.add_hitable(std::make_shared<Triangle>(v3, v2, v6, material));
                scene.add_hitable(std::make_shared<Triangle>(v3, v6, v7, material));
                scene.add_hitable(std::make_shared<Triangle>(v0, v1, v5, material));
                scene.add_hitable(std::make_shared<Triangle>(v0, v5, v4, material));
            }
            else if(type.compare("mesh") == 0) {
                objl::Loader loader;
                std::string mesh_path = "data/meshes/" + mesh_file;
                loader.LoadFile(mesh_path);
                for(int i = 0; i < loader.LoadedMeshes.size(); i++) {
                    objl::Mesh mesh = loader.LoadedMeshes[i];
                    for(int j = 0; j < mesh.Indices.size(); j += 3) {
                        int vrtx_idx;

                        vrtx_idx = mesh.Indices[j];
                        v0 = vec3(mesh.Vertices[vrtx_idx].Position.X, mesh.Vertices[vrtx_idx].Position.Y, mesh.Vertices[vrtx_idx].Position.Z);
                        vrtx_idx = mesh.Indices[j+1];
                        v1 = vec3(mesh.Vertices[vrtx_idx].Position.X, mesh.Vertices[vrtx_idx].Position.Y, mesh.Vertices[vrtx_idx].Position.Z);
                        vrtx_idx = mesh.Indices[j+2];
                        v2 = vec3(mesh.Vertices[vrtx_idx].Position.X, mesh.Vertices[vrtx_idx].Position.Y, mesh.Vertices[vrtx_idx].Position.Z);

                        hitable = std::make_shared<Triangle>(v0, v1, v2, material);
                        if(transfs > 0) {
                            hitable->transform(t);
                        }
                        scene.add_hitable(hitable);
                    }
                }
            }
     	}

    	hitables_file.close();
    }
    else {
    	std::cout << "Error opening hitables file." << std::endl;
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
            else if(s.compare("point") == 0) {
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
            else if(s.compare("spotlight") == 0) {
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
            else if(s.compare("area") == 0) {
                getline(lights_file, s, ' ');
                getline(lights_file, s);
                point3 llc = parse_vector(s);
                lights_file >> s;
                getline(lights_file, s, ' ');
                getline(lights_file, s);
                vec3 horizontal = parse_vector(s);
                lights_file >> s;
                getline(lights_file, s, ' ');
                getline(lights_file, s);
                vec3 vertical = parse_vector(s);
                lights_file >> s;
                getline(lights_file, s, ' ');
                getline(lights_file, s);
                int samples = stoi(s);
                lights_file >> s;
                getline(lights_file, s, ' ');
                getline(lights_file, s);
                rgb diffuse_intensity = parse_vector(s);
                lights_file >> s;
                getline(lights_file, s, ' ');
                getline(lights_file, s);
                rgb specular_intensity = parse_vector(s);
                double height = vertical.length();
                double width = horizontal.length();
                diffuse_intensity /= ((height+1) * (width+1) * samples);
                specular_intensity /= ((height+1) * (width+1) * samples);
                std::random_device rd;
                std::mt19937 gen(rd());
                for(int i = height; i >= 0; i--) {
                    for(int j = 0; j <= width; j++) {
                        for(int k = 0; k < samples; k++) {
                            double u = (double(j) + std::generate_canonical<double,10>(gen)) / (width+1);
                            double v = (double(i) + std::generate_canonical<double,10>(gen)) / (height+1);
                            point3 position = llc + u * horizontal + v * vertical;
                            scene.add_light(std::make_shared<Point_light>(position, diffuse_intensity, specular_intensity));
                        }
                    }
                }
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