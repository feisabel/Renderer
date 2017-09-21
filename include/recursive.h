#ifndef _RECURSIVE_H_
#define _RECURSIVE_H_

#include "material.h"
#include "shader.h"

class Recursive: public Shader {
	private:
		int max_steps;

	public:
		Recursive(int s_=0) : max_steps(s_) {} 
			
		rgb color(const Ray& ray, const Scene& scene) const;
		rgb recursive_color(const Ray& ray, const Scene& scene, int step) const;
};

#endif