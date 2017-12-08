#ifndef _LIGHT_MATERIAL_H_
#define _LIGHT_MATERIAL_H_

#include "material.h"

class Light_material : public Material {
	private:
		std::shared_ptr<Texture> texture;
	public:
		Light_material(std::shared_ptr<Texture> t_) : texture(t_) {}
		
		bool scatter(const Ray& ray, const hit_record& rec, vec3& attenuation, Ray& scattered) const {
			return false;
		}

		vec3 emit(double u, double v, const vec3& p) const {
			return texture->value(u, v, p);
		}
};

#endif