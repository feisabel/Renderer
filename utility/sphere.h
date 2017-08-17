#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "vec3.h"

class Sphere {
	typedef float real_type;

	private:
		point3 center;
		real_type radius;

	public:

		Sphere(point3 c_=point3(), real_type r_=0.f) 
			: center(c_), radius(r_) {}

		inline point3 get_center(void) const { return center; }
		inline real_type get_radius(void) const { return radius; }

};

#endif