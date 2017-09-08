#ifndef _BLINN_PHONG_H_
#define _BLINN_PHONG_H_

#include "material.h"
#include "shader.h"
#include "bp_material.h"

class Blinn_phong : public Shader{
	private:
		bool shadow;
	public:
		Blinn_phong() { shadow = false; }

		void set_shadow(bool s_) { shadow = s_; }
		rgb color(const Ray& ray, const Scene& scene) const;
};

#endif