#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "glm/glm.hpp"

#include "EntityRenderer.h"
#include "Shader/StaticShader.h"
#include "Skybox/SkyboxRenderer.h"
#include "TerrainRenderer.h"

#include "Entity/Camera.h"
#include "Entity/Entity.h"
#include "Entity/Light.h"
#include "Model/TexturedModel.h"

#include <map>
#include <vector>

class MasterRenderer {
public:
  MasterRenderer(Loader *loader);
  void render(std::vector<Light *> lights, Camera *camera);
  void renderScene(const std::vector<Entity *> &entities,
                   std::vector<std::vector<Terrain *>> &terrains,
                   const std::vector<Light *> &lights, Player *player,
                   Camera *camera);
  void prepare();
  void processEntity(Entity *entity);
  void processTerrain(Terrain *terrain);
  void createProjectionMatrix();
  void cleanup();

  static void enableCulling();
  static void disableCulling();

private:
  StaticShader *entityShader;
  EntityRenderer *entityRenderer;

  TerrainShader *terrainShader;
  TerrainRenderer *terrainRenderer;

  SkyboxShader *skyboxShader;
  SkyboxRenderer *skyboxRenderer;

  glm::mat4 projectionMatrix;
  std::map<TexturedModel *, std::vector<Entity *>> entities;
  std::vector<Terrain *> terrains;

  int previousTerrainGridX = 0;
  int previousTerrainGridZ = 0;
};

#endif // !MASTERRENDERER_H
