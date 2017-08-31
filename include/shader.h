#ifndef _SHADER_H_
#define _SHADER_H_

#include "scene.h"

class Shader {
	public:
		virtual rgb color(const Ray& ray, const Scene &scene) const = 0;

};

#endif