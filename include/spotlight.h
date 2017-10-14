#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_

#include "light.h"

class Spotlight : public Light {
	private:
		point3 position;
		vec3 direction;
		double angle;
	public:
		Spotlight(point3 p_, vec3 d_, double a_, rgb di_, rgb si_) 
			: position(p_), direction(d_), angle(a_), Light(di_, si_) {}

		vec3 get_direction(point3 p) const { return -direction; }
		Ray get_ray(point3 p, vec3 n) const { 
			vec3 dir = position - p;
			return Ray(p + 0.01*n, unit_vector(dir), 0.01, dir.length());
		}
		rgb get_diffuse_intensity(point3 p) const { 
			if(isLightened(p)) {
				return diffuse_intensity;
			}
			else {
				return rgb(0,0,0);
			}

		}
		rgb get_specular_intensity(point3 p) const {
			if(isLightened(p)) {
				return specular_intensity;
			}
			else {
				return rgb(0,0,0);
			}
		}
		bool isLightened(point3 p) const {
			return acos(dot(unit_vector(p-position), unit_vector(direction))) <= angle;
		}
};

#endif