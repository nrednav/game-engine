#ifndef SKYBOXRENDERER_H
#define SKYBOXRENDERER_H

#include "Model/RawModel.h"
#include "SkyboxShader.h"
#include "Constants.h"

#include <vector>
#include <string>

class SkyboxRenderer {
public:
	SkyboxRenderer(
		SkyboxShader* shader, Loader* loader, glm::mat4 projectionMatrix
	);
	void render(Camera* camera, glm::vec3 color);

private:
	float SIZE = SKYBOX_SIZE;
	std::vector<float> vertices = {
		-SIZE,  SIZE, -SIZE,
	    -SIZE, -SIZE, -SIZE,
	    SIZE, -SIZE, -SIZE,
	     SIZE, -SIZE, -SIZE,
	     SIZE,  SIZE, -SIZE,
	    -SIZE,  SIZE, -SIZE,

	    -SIZE, -SIZE,  SIZE,
	    -SIZE, -SIZE, -SIZE,
	    -SIZE,  SIZE, -SIZE,
	    -SIZE,  SIZE, -SIZE,
	    -SIZE,  SIZE,  SIZE,
	    -SIZE, -SIZE,  SIZE,

	     SIZE, -SIZE, -SIZE,
	     SIZE, -SIZE,  SIZE,
	     SIZE,  SIZE,  SIZE,
	     SIZE,  SIZE,  SIZE,
	     SIZE,  SIZE, -SIZE,
	     SIZE, -SIZE, -SIZE,

	    -SIZE, -SIZE,  SIZE,
	    -SIZE,  SIZE,  SIZE,
	     SIZE,  SIZE,  SIZE,
	     SIZE,  SIZE,  SIZE,
	     SIZE, -SIZE,  SIZE,
	    -SIZE, -SIZE,  SIZE,

	    -SIZE,  SIZE, -SIZE,
	     SIZE,  SIZE, -SIZE,
	     SIZE,  SIZE,  SIZE,
	     SIZE,  SIZE,  SIZE,
	    -SIZE,  SIZE,  SIZE,
	    -SIZE,  SIZE, -SIZE,

	    -SIZE, -SIZE, -SIZE,
	    -SIZE, -SIZE,  SIZE,
	     SIZE, -SIZE, -SIZE,
	     SIZE, -SIZE, -SIZE,
	    -SIZE, -SIZE,  SIZE,
	     SIZE, -SIZE,  SIZE
	};

	std::vector<std::string> dayTextureFiles = {
		"right_skybox", "left_skybox", "top_skybox",
		"bottom_skybox", "back_skybox", "front_skybox"
	};

	std::vector<std::string> nightTextureFiles = {
		"nightRight", "nightLeft", "nightTop",
		"nightBottom", "nightBack", "nightFront"
	};

	int dayTextureID;
	int nightTextureID;

	RawModel* cube;
	SkyboxShader* shader;

	float time = 0.0f;

	void bindTextures();
	float getBlendFactor();
};

#endif // !SKYBOXRENDERER_H
