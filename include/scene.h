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

struct Light {
	vec3 direction;
	rgb diffuse_intensity;
	rgb specular_intensity;
	Light(vec3 d_=vec3(), rgb di_=rgb(), rgb si_=rgb())
		: direction(d_), diffuse_intensity(di_), specular_intensity(si_) {}
};

class Scene {
	private:
		std::vector<std::shared_ptr<Hitable>> hitables;
		std::vector<std::shared_ptr<Light>> lights;
		rgb ambient_light;
		Background background;

	public:
		Scene() {}

		void add_hitable(std::shared_ptr<Hitable> hitable) { hitables.push_back(hitable); }
		void add_light(std::shared_ptr<Light> light) { lights.push_back(light); }
		void add_ambient_light(rgb light) { ambient_light = light; }

		bool hit(const Ray &ray, double t_min, double t_max, hit_record &rec) const;

		rgb get_background_upper_left() const { return background.upper_left; }
		rgb get_background_upper_right() const { return background.upper_right; }
		rgb get_background_lower_left() const { return background.lower_left; }
		rgb get_background_lower_right() const { return background.lower_right; }

		void set_background_upper_left(rgb ul_) { background.upper_left = ul_; }
		void set_background_upper_right(rgb ur_) { background.upper_right = ur_; }
		void set_background_lower_left(rgb ll_) { background.lower_left = ll_; }
		void set_background_lower_right(rgb lr_) { background.lower_right = lr_; }

		rgb get_ambient_light() const { return ambient_light; }
		std::vector<std::shared_ptr<Light>> get_lights() const { return lights; }

};

#endif