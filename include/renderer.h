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

	public:
		Renderer(Scene& sc_, Image& i_, Camera& c_)
			: scene(sc_), image(i_), camera(c_) { }

		void render(char* buffer, std::unique_ptr<Shader>& shader);
};

#endif