#ifndef _DIRECTION_LIGHT_H_
#define _DIRECTION_LIGHT_H_

#include "light.h"

class Direction_light : public Light {
	private:
		vec3 direction;
	public:
		Direction_light(vec3 d_, rgb di_, rgb si_) 
			: direction(d_), Light(di_, si_) {}

		vec3 get_direction(point3 p) const { return -direction; }
		Ray get_ray(point3 p, vec3 n) const { 
			return Ray(p + 0.0001*n, unit_vector(-direction)); 
		}
		rgb get_diffuse_intensity(point3 p) const { return diffuse_intensity; }
		rgb get_specular_intensity(point3 p) const { return specular_intensity; }
};

#endif