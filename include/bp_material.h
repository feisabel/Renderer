#ifndef _BP_MATERIAL_H_
#define _BP_MATERIAL_H_

#include "material.h"

class BP_material : public Material {
	private:
		rgb ks;
		rgb ka;
		rgb kd;
		float alpha;
		
	public:
		BP_material(rgb ks_=rgb(), rgb ka_=rgb(), rgb kd_=rgb(), float a_=0) 
			: ks(ks_), ka(ka_), kd(kd_), alpha(a_) {}

		rgb get_ks(void) { return ks; }
		rgb get_kd(void) { return kd; }
		rgb get_ka(void) { return ka; }
		float get_alpha(void) { return alpha; }

		bool scatter(const Ray& ray, const hit_record& rec, vec3& attenuation, Ray& scattered) const { return true; }
};

#endif