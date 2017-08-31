#ifndef _NORMAL2RGB_H_
#define _NORMAL2RGB_H_

#include "shader.h"

class Normal2RGB: public Shader {
	public:
		rgb color(const Ray& ray, const Scene& scene) const;
};


#endif