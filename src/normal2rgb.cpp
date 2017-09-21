#include "../include/normal2rgb.h"

rgb Normal2RGB::color(const Ray& ray, const Scene& scene) const {
	hit_record rec;

    if (scene.hit(ray, 0, std::numeric_limits<double>::max(), rec)) {
        //colors the spheres with their normals
        return (rec.normal + vec3(1, 1, 1))/2;
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