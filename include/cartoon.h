#ifndef _CARTOON_H_
#define _CARTOON_H_

#include "material.h"
#include "shader.h"
#include "gradient.h"

class Cartoon: public Shader {

	public:
		Cartoon() {} 
			
		rgb color(const Ray& ray, const Scene& scene) const;
};

#endif