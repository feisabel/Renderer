#include "../include/metal.h"

bool Metal::scatter(const Ray& ray, const hit_record& rec, vec3& attenuation, Ray& scattered) const {
	vec3 reflected = unit_vector(ray.get_direction()) - 2 * dot(unit_vector(ray.get_direction()), rec.normal) * rec.normal;
	scattered = Ray(rec.p+0.01*rec.normal, reflected + fuzziness * random_unit_vector());
	attenuation = texture->value(rec.u, rec.v, rec.p);
	return (dot(scattered.get_direction(), rec.normal) > 0);
}