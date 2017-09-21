#ifndef _DEPTH_MAP_H_
#define _DEPTH_MAP_H_

#include "shader.h"

class Depth_map: public Shader {
	private:
		double max_depth;
		rgb background;
		rgb foreground;
		
	public:
		Depth_map(double m_=0, rgb b_=rgb(), rgb f_=rgb()) 
			: max_depth(m_), background(b_), foreground(f_) {}

		rgb color(const Ray& ray, const Scene& scene) const;
};

#endif