#include "../include/perlin_texture.h"

vec3 Perlin_texture::value(double u, double v, const vec3& p) const {
	return vec3(1,1,1) * 0.5 * (1 + sin(scale * p.z() + 5 * turbulance(scale * p)));
	noise(scale * p);
}

void Perlin_texture::generate_permutation(std::vector<int>& v) {
	for(int i = 0; i < 256; i++) {
		v.push_back(i);
	}
	std::random_device rd;
    std::mt19937 gen(rd());
	for(int i = 255; i > 0; i--) {
    	double random = std::generate_canonical<double,10>(gen);
		int target = int(random*(i+1));
		int vi = v[i];
		v[i] = v[target];
		v[target] = vi;
	}
}

void Perlin_texture::perlin_generate(std::vector<vec3>& v) {
	std::random_device rd;
    std::mt19937 gen(rd());
	for(int i = 0; i < 256; i++) {
		v.push_back(unit_vector(vec3(-1 + 2 * std::generate_canonical<double,10>(gen),
									 -1 + 2 * std::generate_canonical<double,10>(gen),
									 -1 + 2 * std::generate_canonical<double,10>(gen))));
	}
}

double Perlin_texture::turbulance(vec3 p, int depth) const {
	double accum = 0;
	double weight = 1;
	for(int i = 0; i < depth; i++) {
		accum += weight * noise(p);
		weight *= 0.5;
		p *= 2;
	}
	return abs(accum);
}

double Perlin_texture::noise(const vec3& p) const {
	int i = floor(p.x());
	int j = floor(p.y());
	int k = floor(p.z());
	double u = p.x() - i;
	double v = p.y() - j;
	double w = p.z() - k;
	double uu = u*u*(3-2*u);
	double vv = v*v*(3-2*v);
	double ww = w*w*(3-2*w);
	double accum = 0;
	for(int di = 0; di < 2; di++) {
		for(int dj = 0; dj < 2; dj++) {
			for(int dk = 0; dk < 2; dk++) {
				accum += (di * uu + (1-di) * (1-uu)) *
						 (dj * vv + (1-dj) * (1-vv)) *
						 (dk * ww + (1-dk) * (1-ww)) *
						 dot(random_vec[x_perm[(i+di) & 255] ^ y_perm[(j+dj) & 255] ^ z_perm[(k+dk) & 255]], 
						 	 vec3(u-di, v-dj, w-dk));
			}
		}
	}
	return accum;
}