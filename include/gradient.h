#ifndef _GRADIENT_H_
#define _GRADIENT_H_

#include "material.h"

class Gradient : public Material {
	private:
		int n;
		std::vector<rgb> colors;
		std::vector<double> partitions;
		rgb outline_color;
		rgb shadow_color;

	public:
		Gradient(int n_, rgb o_, rgb s_, std::vector<rgb> c_, std::vector<double> p_)
			: n(n_), outline_color(o_), shadow_color(s_), colors(c_), partitions(p_) {}

		int get_n() { return n; }
		double get_partition(int i) { return partitions[i]; }
		rgb get_color(int i) { return colors[i]; }
		rgb get_outline_color() { return outline_color; }
		rgb get_shadow() { return shadow_color; }

		bool scatter(const Ray& ray, const hit_record& rec, vec3& attenuation, Ray& scattered) const { return true; }
};

#endif