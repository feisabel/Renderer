#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "hitable.h"

class Sphere: public Hitable {
	typedef float real_type;

	private:
		point3 center;
		real_type radius;

	public:

		Sphere(point3 c_=point3(), real_type r_=0.f) 
			: center(c_), radius(r_) {}

		inline point3 get_center(void) const { return center; }
		inline real_type get_radius(void) const { return radius; }

		bool hit(const Ray &ray, float t_min, float t_max, hit_record &rec) const;

};

#endif