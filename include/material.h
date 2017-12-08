#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "hitable.h"
#include "texture.h"

class Material {
	public:
		virtual bool scatter(const Ray& ray, const hit_record& rec, vec3& attenuation, Ray& scattered) const = 0;
		virtual vec3 emit(double u, double v, const vec3& p) const {
			return vec3(0,0,0);
		}
};

#endif