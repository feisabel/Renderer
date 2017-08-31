#ifndef _DIFFUSE_H_
#define _DIFFUSE_H_

#include "shader.h"

class Diffuse: public Shader {
	private:
		float max_steps;

	public:
		Diffuse(float s_=0) : max_steps(s_) {} 
			
		rgb color(const Ray& ray, const Scene& scene) const;
		rgb recursive_color(const Ray& ray, const Scene& scene, int step) const;
};

#endif