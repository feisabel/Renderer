#include "../include/blinn_phong.h"

rgb Blinn_phong::color(const Ray& ray, const Scene& scene) const {
	hit_record rec, aux;

    if (scene.hit(ray, rec)) {
    	std::vector<std::shared_ptr<Light>> lights = scene.get_lights();
    	std::shared_ptr<BP_material> material = std::dynamic_pointer_cast<BP_material>(rec.material);
    	vec3 unit_normal = unit_vector(rec.normal);
    	vec3 unit_ray = unit_vector(-ray.get_direction());
  		vec3 diffuse = rgb(0, 0, 0);
  		vec3 specular = rgb(0, 0, 0);
    	for(int i = 0; i < lights.size(); i++) {
    		vec3 unit_light = unit_vector(lights[i]->get_direction(rec.p)); 
            if(!shadow || !scene.hit(lights[i]->get_ray(rec.p, rec.normal), aux)) {
                double d = fmax(dot(unit_light, unit_normal), 0.0);
    	 		double s = pow(fmax(dot(unit_normal, unit_vector(unit_light + unit_ray)), 0.0), 
    	   			material->get_alpha());
    	    	diffuse += material->get_kd() * d * lights[i]->get_diffuse_intensity(rec.p);
    	    	specular += material->get_ks() * s * lights[i]->get_specular_intensity(rec.p);
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
        double x_ratio = (unit_ray.x()+1.0)/2.0;
        double y_ratio = (unit_ray.y()+1.0)/2.0;

        //colors the background with bilinear interpolation
        rgb left = lerp(y_ratio, scene.get_background_upper_left(), scene.get_background_lower_left());
        rgb right = lerp(y_ratio, scene.get_background_upper_right(), scene.get_background_lower_right());
        return lerp(x_ratio, right, left);
    }
}