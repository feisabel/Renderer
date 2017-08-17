#include "../utility/scene.h"

bool Scene::hit(const Ray &ray, float t_min, float t_max, hit_record &rec) const {
	bool hit_anything = false;
	float closest = t_max;
	hit_record temp_rec;
	for (int i = 0; i < hitables.size(); i++) {
		if (hitables[i]->hit(ray, t_min, t_max, temp_rec)) {
			hit_anything = true;
			if (temp_rec.t < closest) {
				closest = temp_rec.t;
				rec = temp_rec;
			}
		}
	}
	return hit_anything;
}