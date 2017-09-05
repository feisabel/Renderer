#include "../include/recursive.h"

rgb Recursive::color(const Ray& ray, const Scene& scene) const {
	return recursive_color(ray, scene, max_steps);
}

rgb Recursive::recursive_color(const Ray& ray, const Scene& scene, int step) const {
	hit_record rec;

    if(step == 0) {
        return rgb(0, 0, 0);
    }
    if (scene.hit(ray, 0.001, std::numeric_limits<float>::max(), rec)) {
        vec3 attenuation;
        Ray scattered;
        rec.material->scatter(ray, rec, attenuation, scattered);
        return attenuation  * recursive_color(scattered, scene, step-1);
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