#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "hitable.h"

class Sphere: public Hitable {
	typedef double real_type;

	private:
		point3 center;
		real_type radius;
		std::shared_ptr<Material> material;

	public:
		Sphere(point3 c_=point3(), real_type r_=0, std::shared_ptr<Material> m_=nullptr) 
			: center(c_), radius(r_), material(m_) {}

		inline point3 get_center(void) const { return center; }
		inline real_type get_radius(void) const { return radius; }

		bool hit(const Ray &ray, hit_record &rec) const;

		void transform(mat4& t);

};

#endif