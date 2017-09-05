#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "hitable.h"

class Sphere: public Hitable {
	typedef float real_type;

	private:
		point3 center;
		real_type radius;
		std::shared_ptr<Material> material;
		rgb ks;
		rgb ka;
		rgb kd;
		float p;

	public:
		Sphere(point3 c_=point3(), real_type r_=0, std::shared_ptr<Material> m_=nullptr, float ks_=0, float ka_=0, float kd_=0, float p_=0) 
			: center(c_), radius(r_), material(m_), ks(ks_), ka(ka_), kd(kd_), p(p_) {}

		inline point3 get_center(void) const { return center; }
		inline real_type get_radius(void) const { return radius; }

		bool hit(const Ray &ray, float t_min, float t_max, hit_record &rec) const;

};

#endif