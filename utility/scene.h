#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>

#include "hitable.h"

class Scene {
	private:
		std::vector<Hitable*> hitables;

	public:
		Scene() {}
		void add_hitable(Hitable* hitable) { hitables.push_back(hitable); }
		bool hit(const Ray &ray, float t_min, float t_max, hit_record &rec) const;

};

#endif