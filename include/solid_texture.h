#ifndef _SOLID_TEXTURE_H_
#define _SOLID_TEXTURE_H_

#include "texture.h"

class Solid_texture : public Texture {
	private:
		rgb color;
	public:
		Solid_texture(rgb c_) : color(c_) {}
		vec3 value(double u, double v, const vec3& p) const { return color; }
};

#endif