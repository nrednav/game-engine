#ifndef TERRAINRENDERER_H
#define TERRAINRENDERER_H

#include "Entity/Entity.h"
#include "Model/TexturedModel.h"
#include "Shader/TerrainShader.h"
#include "Terrain/Terrain.h"
#include "glm/glm.hpp"

#include <vector>

class TerrainRenderer {
public:
  TerrainRenderer(TerrainShader *shader, glm::mat4 &projectionMatrix);
  void render(std::vector<Terrain *> &terrains);
  void prepareTerrain(Terrain *terrain);
  void bindTextures(Terrain *terrain);
  void unbindTerrainModel();
  void loadModelMatrix(Terrain *terrain);

private:
  TerrainShader *shader;
};

#endif // !TERRAINRENDERER_H
