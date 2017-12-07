#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "hitable.h"
#include "texture.h"

class Material {
	public:
		virtual bool scatter(const Ray& ray, const hit_record& rec, vec3& attenuation, Ray& scattered) const = 0;
};

#endif