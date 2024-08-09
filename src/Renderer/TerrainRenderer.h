#ifndef TERRAINRENDERER_H
#define TERRAINRENDERER_H

#include "Shader/TerrainShader.h"
#include "Terrain/Terrain.h"
#include <vector>

class TerrainRenderer {
public:
  TerrainRenderer(TerrainShader* shader, glm::mat4& projection_matrix);
  void render(std::vector<Terrain*>& terrains);
  void prepare_terrain(Terrain* terrain);
  void bind_textures(Terrain* terrain);
  void unbind_terrain_model();
  void load_model_matrix(Terrain* terrain);

private:
  TerrainShader* shader;
};

#endif // !TERRAINRENDERER_H
