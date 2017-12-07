#ifndef _METAL_H_
#define _METAL_H_

#include "material.h"

class Metal : public Material {
	private:
		std::shared_ptr<Texture> texture;
		double fuzziness;
	public:
		Metal(std::shared_ptr<Texture> t_, double f_) : texture(t_), fuzziness(f_) {}
		
		bool scatter(const Ray& ray, const hit_record& rec, vec3& attenuation, Ray& scattered) const;
};

#endif