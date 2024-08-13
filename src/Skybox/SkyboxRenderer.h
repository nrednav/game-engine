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
    SkyboxShader* shader,
    Loader* loader,
    glm::mat4 projection_matrix,
    Display* display
  );

  void render(Camera* camera, glm::vec3 color);

private:
  Display* display;

  float SIZE = SKYBOX_SIZE;

  std::vector<float> vertices = {
    -SIZE, SIZE,  -SIZE, -SIZE, -SIZE, -SIZE, SIZE,  -SIZE, -SIZE,
    SIZE,  -SIZE, -SIZE, SIZE,  SIZE,  -SIZE, -SIZE, SIZE,  -SIZE,

    -SIZE, -SIZE, SIZE,  -SIZE, -SIZE, -SIZE, -SIZE, SIZE,  -SIZE,
    -SIZE, SIZE,  -SIZE, -SIZE, SIZE,  SIZE,  -SIZE, -SIZE, SIZE,

    SIZE,  -SIZE, -SIZE, SIZE,  -SIZE, SIZE,  SIZE,  SIZE,  SIZE,
    SIZE,  SIZE,  SIZE,  SIZE,  SIZE,  -SIZE, SIZE,  -SIZE, -SIZE,

    -SIZE, -SIZE, SIZE,  -SIZE, SIZE,  SIZE,  SIZE,  SIZE,  SIZE,
    SIZE,  SIZE,  SIZE,  SIZE,  -SIZE, SIZE,  -SIZE, -SIZE, SIZE,

    -SIZE, SIZE,  -SIZE, SIZE,  SIZE,  -SIZE, SIZE,  SIZE,  SIZE,
    SIZE,  SIZE,  SIZE,  -SIZE, SIZE,  SIZE,  -SIZE, SIZE,  -SIZE,

    -SIZE, -SIZE, -SIZE, -SIZE, -SIZE, SIZE,  SIZE,  -SIZE, -SIZE,
    SIZE,  -SIZE, -SIZE, -SIZE, -SIZE, SIZE,  SIZE,  -SIZE, SIZE
  };

  std::vector<std::string> day_texture_filepaths = {
    "assets/textures/skybox/day/right.png",
    "assets/textures/skybox/day/left.png",
    "assets/textures/skybox/day/top.png",
    "assets/textures/skybox/day/bottom.png",
    "assets/textures/skybox/day/back.png",
    "assets/textures/skybox/day/front.png"
  };

  std::vector<std::string> night_texture_filepaths = {
    "assets/textures/skybox/night/right.png",
    "assets/textures/skybox/night/left.png",
    "assets/textures/skybox/night/top.png",
    "assets/textures/skybox/night/bottom.png",
    "assets/textures/skybox/night/back.png",
    "assets/textures/skybox/night/front.png",
  };

  int day_texture_id;
  int night_texture_id;

  RawModel* cube;
  SkyboxShader* shader;

  float time = 0.0f;

  void bind_textures();
  float get_blend_factor();
};

#endif // !SKYBOXRENDERER_H
