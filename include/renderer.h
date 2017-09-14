#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "shader.h"
#include "camera.h"
#include "image.h"

class Renderer {
	private:
		Scene& scene;
		Image& image;
		Camera& camera;
		int samples;

	public:
		Renderer(Scene& sc_, Image& i_, Camera& c_, int s_)
			: scene(sc_), image(i_), camera(c_), samples(s_) { }

		void render(char* buffer, Shader& shader);
};

#endif