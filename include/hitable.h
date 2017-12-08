#ifndef _HITABLE_H_
#define _HITABLE_H_

#include "ray.h"
#include <memory>

class Material;

struct hit_record {
	double t;
	double u;
	double v;
	point3 p;
	vec3 normal;
	std::shared_ptr<Material> material;
};

class Hitable {
	public:
		virtual ~Hitable() {}
		virtual bool hit(const Ray &ray, hit_record &rec) const = 0;
		virtual void transform(mat4& t) = 0;
};

#endif