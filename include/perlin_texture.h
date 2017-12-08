#ifndef _PERLIN_TEXTURE_H_
#define _PERLIN_TEXTURE_H_

#include "texture.h"
#include <vector>

class Perlin_texture : public Texture {
	private:
		std::vector<int> x_perm;
		std::vector<int> y_perm;
		std::vector<int> z_perm;
		std::vector<vec3> random_vec;
		double scale;
	public:
		Perlin_texture(double s_) {
			generate_permutation(x_perm);
			generate_permutation(y_perm);
			generate_permutation(z_perm);
			perlin_generate(random_vec);
			scale = s_;
		}

		vec3 value(double u, double v, const vec3& p) const;

		double noise(const vec3& p) const;
		void generate_permutation(std::vector<int>& v);
		void perlin_generate(std::vector<vec3>& v);
		double turbulance(vec3 p, int depth = 7) const;
};

#endif