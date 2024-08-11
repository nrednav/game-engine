#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "EntityRenderer.h"
#include "Shader/StaticShader.h"
#include "Skybox/SkyboxRenderer.h"
#include "TerrainRenderer.h"

#include "Entity/Camera.h"
#include "Entity/Entity.h"
#include "Entity/Light.h"
#include "Model/TexturedModel.h"

#include <map>
#include <memory>
#include <vector>

class MasterRenderer {
public:
  MasterRenderer(Loader* loader);
  void render(std::vector<Light*> lights, Camera* camera);
  void render_scene(
    const std::vector<Entity*>& entities,
    std::vector<std::vector<std::unique_ptr<Terrain>>>& terrains,
    const std::vector<Light*>& lights,
    Player* player,
    Camera* camera
  );
  void prepare();
  void process_entity(Entity* entity);
  void process_terrain(Terrain* terrain);
  void create_projection_matrix();
  void cleanup();

  static void enable_culling();
  static void disable_culling();

private:
  StaticShader* entity_shader;
  EntityRenderer* entity_renderer;

  TerrainShader* terrain_shader;
  TerrainRenderer* terrain_renderer;

  SkyboxShader* skybox_shader;
  SkyboxRenderer* skybox_renderer;

  glm::mat4 projection_matrix;
  std::map<TexturedModel*, std::vector<Entity*>> entities;
  std::vector<Terrain*> terrains;

  int previous_terrain_grid_x = 0;
  int previous_terrain_grid_z = 0;
};

#endif // !MASTERRENDERER_H
