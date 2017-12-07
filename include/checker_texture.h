#ifndef _CHECKER_TEXTURE_H_
#define _CHECKER_TEXTURE_H_

#include "texture.h"

class Checker_texture : public Texture {
	private:
		std::shared_ptr<Texture> odd;
		std::shared_ptr<Texture> even;
	public:
		Checker_texture(std::shared_ptr<Texture> o_, std::shared_ptr<Texture> e_) 
			: odd(o_), even(e_) {}
		vec3 value(double u, double v, const vec3& p) const { 
			double sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
			if(sines < 0) {
				return odd->value(u, v, p);
			}
			else {
				return even->value(u, v, p);
			}
		}
};

#endif