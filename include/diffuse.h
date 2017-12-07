#ifndef _DIFFUSE_H_
#define _DIFFUSE_H_

#include "material.h"

class Diffuse : public Material {
	private:
		std::shared_ptr<Texture> texture;
	public:
		Diffuse(std::shared_ptr<Texture> t_) : texture(t_) {}
		
		bool scatter(const Ray& ray, const hit_record& rec, vec3& attenuation, Ray& scattered) const;
};

#endif