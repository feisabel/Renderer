#include "../include/triangle.h"

bool Triangle::hit(const Ray &ray, hit_record &rec) const {
	vec3 e1 = v1 - v0;
	vec3 e2 = v2 - v0;
	vec3 P = cross(ray.get_direction(), e2);
	double det = dot(e1, P);

	if(det < 0.0001) {
		return false;
	}

	vec3 T = ray.get_origin() - v0;
	double u = dot(P, T);

	if(u < 0 || u > det) {
		return false;
	}

	vec3 Q = cross(T, e1);
	double v = dot(Q, ray.get_direction());

	if(v < 0 || u + v > det) {
		return false;
	}

	double t = dot(Q, e2);
	t /= det;
	u /= det;
	v /= det;

	rec.t = t;
	rec.p = ray.point_at(t);
	rec.normal = unit_vector(cross(e1,e2));
	rec.material = material;
	return true;
}