#include "../include/scene.h"

bool Scene::hit(const Ray &ray, hit_record &rec) const {
	bool hit_anything = false;
	double closest = ray.get_t_max();
	hit_record temp_rec;
	for (int i = 0; i < hitables.size(); i++) {
		if (hitables[i]->hit(ray, temp_rec)) {
			hit_anything = true;
			if (temp_rec.t < closest) {
				closest = temp_rec.t;
				rec = temp_rec;
			}
		}
	}
	return hit_anything;
}