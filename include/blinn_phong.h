#ifndef _BLINN_PHONG_H_
#define _BLINN_PHONG_H_

#include "material.h"
#include "shader.h"
#include "bp_material.h"

class Blinn_phong : public Shader{
	public:
		Blinn_phong() {}

		rgb color(const Ray& ray, const Scene& scene) const;
};

#endif