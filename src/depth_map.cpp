#include "../include/depth_map.h"

rgb Depth_map::color(const Ray& ray, const Scene& scene) const {
	hit_record rec;

    if (scene.hit(ray, rec)) {
        double length = (rec.p - ray.get_origin()).length();
        if(length > max_depth) {
            return background;
        }
        //colors the spheres with linear interpolation of their distances from the camera
        return lerp(length/max_depth, background, foreground);
    }
    else {
        return background;
    }
}