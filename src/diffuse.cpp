#include "../include/diffuse.h"

bool Diffuse::scatter(const Ray& ray, const hit_record& rec, vec3& attenuation, Ray& scattered) const {
	scattered = Ray(rec.p+0.001*rec.normal, rec.normal + random_unit_vector());
	attenuation = texture->value(rec.u, rec.v, rec.p);
	return true;
}