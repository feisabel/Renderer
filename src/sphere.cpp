#include "../include/sphere.h"

bool Sphere::hit(const Ray &ray, float t_min, float t_max, hit_record &rec) const {
	vec3 direction = ray.get_direction();
    vec3 center_direction = ray.get_origin() - center;

    float a = dot(direction, direction);
    float b = 2 * dot(center_direction, direction);
    float c = dot(center_direction, center_direction) - radius * radius;
    float delta = b * b - 4 * a * c;
    if (delta >= 0) {
        float t = (-b - sqrt(delta)) / (2 * a);
        if (t >= t_min && t <= t_max) {
        	rec.t = t;
        	rec.p = ray.point_at(t);
        	rec.normal = unit_vector(rec.p - center);
            rec.material = material;
        	return true;
        }
        t = (-b - sqrt(delta)) / (2 * a);
        if (t >= t_min && t <= t_max) {
        	rec.t = t;
        	rec.p = ray.point_at(t);
        	rec.normal = unit_vector(rec.p - center);
            rec.material = material;
        	return true;
        }
    }
    return false;
}