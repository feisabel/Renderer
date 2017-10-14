#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "light.h"

class Point_light : public Light {
	private:
		point3 position;
	public:
		Point_light(point3 p_, rgb di_, rgb si_) 
			: position(p_), Light(di_, si_) {}

		vec3 get_direction(point3 p) const { return (position - p); }
		Ray get_ray(point3 p, vec3 n) const {
			vec3 direction = position - p;
			return Ray(p + 0.0001*n, unit_vector(direction), 0.0001, direction.length());
		}
		rgb get_diffuse_intensity(point3 p) const { return diffuse_intensity; }
		rgb get_specular_intensity(point3 p) const { return specular_intensity; }
};

#endif