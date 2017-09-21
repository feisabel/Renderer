#ifndef _HITABLE_H_
#define _HITABLE_H_

#include "ray.h"
#include <memory>

class Material;

struct hit_record {
	double t;
	point3 p;
	vec3 normal;
	std::shared_ptr<Material> material;
};

class Hitable {
	public:
		virtual ~Hitable() {}
		virtual bool hit(const Ray &ray, double t_min, double t_max, hit_record &rec) const = 0;

};

#endif