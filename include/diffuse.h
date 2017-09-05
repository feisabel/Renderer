#ifndef _DIFFUSE_H_
#define _DIFFUSE_H_

#include "material.h"

class Diffuse : public Material {
	private:
		vec3 albedo;
	public:
		Diffuse(vec3 a_) : albedo(a_) {}
		
		bool scatter(const Ray& ray, const hit_record& rec, vec3& attenuation, Ray& scattered) const;
};

#endif