#include "../include/cartoon.h"

rgb Cartoon::color(const Ray& ray, const Scene& scene) const {
	hit_record rec,aux;

    if (scene.hit(ray, 0.001, std::numeric_limits<double>::max(), rec)) {
    	std::vector<std::shared_ptr<Light>> lights = scene.get_lights();
    	std::shared_ptr<Gradient> material = std::dynamic_pointer_cast<Gradient>(rec.material);
    	if(dot(rec.normal, unit_vector(-ray.get_direction())) < 0.1) {
    		return material->get_outline_color();
    	}
    	rgb c = rgb(0,0,0);
        double maxr = 0;
        double maxg = 0;
        double maxb = 0;
    	for(int i = 0; i < lights.size(); i++) {
            vec3 unit_light = unit_vector(-lights[i]->direction);
            Ray r(rec.p + 0.0001*rec.normal, unit_light);
    		double cosi = dot(unit_light, rec.normal);
    		if(cosi < 0) {
                rgb pc = material->get_color(material->get_n()-1);
                if(pc[0] > maxr) {
                    c[0] = pc[0];
                    maxr = pc[0];
                }
                if(pc[1] > maxg) {
                    c[1] = pc[1];
                    maxg = pc[1];
                }
                if(pc[2] > maxb) {
                    c[2] = pc[2];
                    maxb = pc[2];
                }
    		}
    		else {
    			cosi = 1 - cosi;
	    		for(int j = material->get_n()-1; j >= 0; j--) {
	    			if(cosi >= material->get_partition(j)) {
	    				rgb pc = material->get_color(j);
                        if(pc[0] > maxr) {
                            c[0] = pc[0];
                            maxr = pc[0];
                        }
                        if(pc[1] > maxg) {
                            c[1] = pc[1];
                            maxg = pc[1];
                        }
                        if(pc[2] > maxb) {
                            c[2] = pc[2];
                            maxb = pc[2];
                        }
        	    		break;
        	    	}
        	    }
            }
    	}
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