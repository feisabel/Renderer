#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "vec3.h"

class Light { 
	protected:
		rgb diffuse_intensity;
		rgb specular_intensity;
	public:
		Light(rgb di_=rgb(), rgb si_=rgb())
			: diffuse_intensity(di_), specular_intensity(si_) {}

		virtual vec3 get_direction(point3 p) const = 0;
		virtual Ray get_ray(point3 p, vec3 n) const = 0;
		virtual rgb get_diffuse_intensity(point3 p) const = 0;
		virtual rgb get_specular_intensity(point3 p) const = 0;
};

#endif