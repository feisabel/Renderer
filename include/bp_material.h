#ifndef _BP_MATERIAL_H_
#define _BP_MATERIAL_H_

#include "material.h"

class BP_material : public Material {
	private:
		rgb ks;
		rgb ka;
		rgb kd;
		double alpha;
		
	public:
		BP_material(rgb ka_ =rgb(), rgb kd_=rgb(), rgb ks_=rgb(), double a_=0) 
			: ka(ka_), kd(kd_), ks(ks_), alpha(a_) {}

		rgb get_ks(void) { return ks; }
		rgb get_kd(void) { return kd; }
		rgb get_ka(void) { return ka; }
		double get_alpha(void) { return alpha; }

		bool scatter(const Ray& ray, const hit_record& rec, vec3& attenuation, Ray& scattered) const { return true; }
};

#endif