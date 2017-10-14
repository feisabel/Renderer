#ifndef _RAY_H_
#define _RAY_H_

#include "vec3.h"

class Ray {

	private:
		point3 origin;
		vec3 direction;
		double t_min;
		double t_max;

	public:
		typedef double real_type;

		Ray() {}
		
		Ray(point3 o_, vec3 d_) : origin(o_), direction(d_) {
			t_min = 0.0001;
			t_max = std::numeric_limits<double>::max();
		}

		Ray(point3 o_, vec3 d_, double mi_, double ma_) 
			: origin(o_), direction(d_), t_min(mi_), t_max(ma_) {}

		inline vec3 get_direction(void) const { return direction; }
		inline point3 get_origin(void) const { return origin; }
		point3 point_at(real_type t_) const { return origin + t_ * direction; }
		void set_t_min(double t_) { t_min = t_; }
		void set_t_max(double t_) { t_max = t_; }
		double get_t_min() const { return t_min; }
		double get_t_max() const { return t_max; }

};

#endif