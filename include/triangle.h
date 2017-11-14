#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "hitable.h"

class Triangle: public Hitable {
	private:
		point3 v0;
		point3 v1;
		point3 v2;
		std::shared_ptr<Material> material;

	public:
		Triangle(point3 v0_, point3 v1_, point3 v2_, std::shared_ptr<Material> m_) 
			: v0(v0_), v1(v1_), v2(v2_), material(m_) {}

		bool hit(const Ray &ray, hit_record &rec) const;
};

#endif