#include "../include/sphere.h"

bool Sphere::hit(const Ray &ray, hit_record &rec) const {
	vec3 direction = ray.get_direction();
    vec3 center_direction = ray.get_origin() - center;

    double a = dot(direction, direction);
    double b = 2 * dot(center_direction, direction);
    double c = dot(center_direction, center_direction) - (radius * radius);
    double delta = b * b - 4 * a * c;
    if (delta >= 0) {
        double t = (-b - sqrt(delta)) / (2.0 * a);
        if (t >= ray.get_t_min() && t <= ray.get_t_max()) {
        	rec.t = t;
        	rec.p = ray.point_at(t);
        	rec.normal = unit_vector(rec.p - center);
            rec.material = material;
        	return true;
        }
        t = (-b + sqrt(delta)) / (2.0 * a);
        if (t >= ray.get_t_min() && t <= ray.get_t_max()) {
        	rec.t = t;
        	rec.p = ray.point_at(t);
        	rec.normal = unit_vector(rec.p - center);
            rec.material = material;
        	return true;
        }
    }
    return false;
}