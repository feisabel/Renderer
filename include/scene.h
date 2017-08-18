#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>

#include "hitable.h"

struct Background {
	rgb upper_left;
    rgb upper_right;
    rgb lower_left;
    rgb lower_right;
};

class Scene {
	private:
		std::vector<Hitable*> hitables;
		Background background;

	public:
		Scene() {}
		~Scene() {
			for(int i = 0; i < hitables.size(); i++) {
				delete hitables[i];
			}
		}

		void add_hitable(Hitable* hitable) { hitables.push_back(hitable); }
		bool hit(const Ray &ray, float t_min, float t_max, hit_record &rec) const;

		rgb get_background_upper_left() { return background.upper_left; }
		rgb get_background_upper_right() { return background.upper_right; }
		rgb get_background_lower_left() { return background.lower_left; }
		rgb get_background_lower_right() { return background.lower_right; }

		void set_background(rgb ul_, rgb ur_, rgb ll_, rgb lr_) {
			background.upper_left = ul_;
			background.upper_right = ur_; 
			background.lower_left = ll_;
			background.lower_right = lr_;
		}

};

#endif