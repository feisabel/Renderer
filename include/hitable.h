#ifndef _HITABLE_H_
#define _HITABLE_H_

#include "ray.h"

struct hit_record {
	float t;
	point3 p;
	vec3 normal;
	rgb albedo;
};

class Hitable {
	public:
		virtual ~Hitable() {}
		virtual bool hit(const Ray &ray, float t_min, float t_max, hit_record &rec) const = 0;

};

#endif