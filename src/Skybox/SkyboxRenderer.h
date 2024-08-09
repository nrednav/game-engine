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
    glm::mat4 projection_matrix
  );

  void render(Camera* camera, glm::vec3 color);

private:
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

  std::vector<std::string> day_texture_files = {
    "skybox/day/right",
    "skybox/day/left",
    "skybox/day/top",
    "skybox/day/bottom",
    "skybox/day/back",
    "skybox/day/front"
  };

  std::vector<std::string> night_texture_files = {
    "skybox/night/right",
    "skybox/night/left",
    "skybox/night/top",
    "skybox/night/bottom",
    "skybox/night/back",
    "skybox/night/front",
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
