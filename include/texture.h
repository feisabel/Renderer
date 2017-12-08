#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "vec3.h"

class Texture {
	public:
		virtual vec3 value(double u, double v, const vec3& p) const = 0;
};

#endif