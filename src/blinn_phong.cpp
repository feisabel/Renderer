#include "../include/blinn_phong.h"

rgb Blinn_phong::color(const Ray& ray, const Scene& scene) const {
	hit_record rec, aux;

    if (scene.hit(ray, 0, std::numeric_limits<float>::max(), rec)) {
    	std::vector<std::shared_ptr<Light>> lights = scene.get_lights();
    	std::shared_ptr<BP_material> material = std::dynamic_pointer_cast<BP_material>(rec.material);
    	vec3 unit_normal = unit_vector(rec.normal);
    	vec3 unit_ray = unit_vector(-ray.get_direction());
  		vec3 diffuse = rgb(0, 0, 0);
  		vec3 specular = rgb(0, 0, 0);
    	for(int i = 0; i < lights.size(); i++) {
    		vec3 unit_light = unit_vector(-lights[i]->direction);
    		Ray r(rec.p + 0.0001*unit_normal, unit_light);
            if(!shadow || !scene.hit(r, 0.0001, std::numeric_limits<float>::max(), aux)) {
        		
                float d = fmax(dot(unit_light, unit_normal), 0.0);
    	 		float s = pow(fmax(dot(unit_normal, unit_vector(unit_light + unit_ray)), 0.0), 
    	   			material->get_alpha());
    	    	diffuse += material->get_kd() * d * lights[i]->diffuse_intensity;
    	    	specular += material->get_ks() * s * lights[i]->specular_intensity;
            }
    	}
        vec3 c =  (material->get_ka() * scene.get_ambient_light()) + diffuse + specular;
        if(c[0] > 1)
        	c[0] = 1;
        if(c[1] > 1)
        	c[1] = 1; 
        if(c[2] > 1)
        	c[2] = 1;
        return c;
    }
    else {
        vec3 unit_ray = unit_vector(ray.get_direction());
        float x_ratio = (unit_ray.x()+1.0)/2.0;
        float y_ratio = (unit_ray.y()+1.0)/2.0;

        //colors the background with bilinear interpolation
        rgb left = lerp(y_ratio, scene.get_background_upper_left(), scene.get_background_lower_left());
        rgb right = lerp(y_ratio, scene.get_background_upper_right(), scene.get_background_lower_right());
        return lerp(x_ratio, right, left);
    }
}