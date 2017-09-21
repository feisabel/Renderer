#ifndef _METAL_H_
#define _METAL_H_

#include "material.h"

class Metal : public Material {
	private:
		vec3 albedo;
		double fuzziness;
	public:
		Metal(vec3 a_, double f_) : albedo(a_), fuzziness(f_) {}
		
		bool scatter(const Ray& ray, const hit_record& rec, vec3& attenuation, Ray& scattered) const;
};

#endif