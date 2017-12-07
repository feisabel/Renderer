#include "../include/diffuse.h"

bool Diffuse::scatter(const Ray& ray, const hit_record& rec, vec3& attenuation, Ray& scattered) const {
	scattered = Ray(rec.p+0.01*rec.normal, rec.normal + random_unit_vector());
	attenuation = texture->value(0, 0, rec.p);
	return true;
}