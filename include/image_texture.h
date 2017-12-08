#ifndef _IMAGE_TEXTURE_H_
#define _IMAGE_TEXTURE_H_

#include "texture.h"

class Image_texture : public Texture {
	private:
		unsigned char* data;
		int width;
		int height;

	public:
		Image_texture(unsigned char* d_, int w_, int h_) 
			: data(d_), width(w_), height(h_) {}
		vec3 value(double u, double v, const vec3& p) const { 
			int i = u * width;
			int j = (1-v) * height - 0.001;
			if(i < 0) {
				i = 0;
			}
			if(j < 0) {
				j = 0;
			} 
			if(i > width - 1) {
				i = width - 1;
			}
			if(j > height - 1) {
				j = height - 1;
			}
			double r = int(data[3 * i + 3 * width * j]) / 255.0;
			double g = int(data[3 * i + 3 * width * j + 1]) / 255.0;
			double b = int(data[3 * i + 3 * width * j + 2]) / 255.0;
			return vec3(r, g, b);
		}
};

#endif