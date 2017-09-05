#include "../include/diffuse.h"

bool Diffuse::scatter(const Ray& ray, const hit_record& rec, vec3& attenuation, Ray& scattered) const {
	scattered = Ray(rec.p, rec.normal + random_unit_vector());
	attenuation = albedo;
	return true;
}