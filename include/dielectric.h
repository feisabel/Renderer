#ifndef _DIELECTRIC_H_
#define _DIELECTRIC_H_

#include "material.h"

class Dielectric : public Material {
	private:
		double refractive_index;
	public:
		Dielectric(double r_) : refractive_index(r_) {}
		
		bool scatter(const Ray& ray, const hit_record& rec, vec3& attenuation, Ray& scattered) const;

		bool refract(vec3 normal, vec3 dir, double n, vec3& refracted) const;

		double schlick(vec3 normal, vec3 dir, double n1, double n2) const;

		double schlick(double cosine, double n1, double n2) const;
};

#endif