#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "Display/Display.h"
#include "EntityRenderer.h"
#include "Floor/Floor.h"
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
  MasterRenderer(Display* display, Loader* loader);
  ~MasterRenderer();

  void
  render(const std::vector<std::unique_ptr<Light>>& lights, Camera* camera);

  void render_scene(
    const std::vector<std::unique_ptr<Entity>>& entities,
    TerrainGrid& terrain_grid,
    const std::vector<std::unique_ptr<Light>>& lights,
    Player* player,
    Camera* camera
  );

  void prepare();
  void process_entity(Entity* entity);
  void process_terrain(Terrain* terrain);
  void create_projection_matrix();

  static void enable_culling();
  static void disable_culling();

private:
  std::unique_ptr<StaticShader> entity_shader;
  std::unique_ptr<EntityRenderer> entity_renderer;

  std::unique_ptr<TerrainShader> terrain_shader;
  std::unique_ptr<TerrainRenderer> terrain_renderer;

  std::unique_ptr<SkyboxShader> skybox_shader;
  std::unique_ptr<SkyboxRenderer> skybox_renderer;

  glm::mat4 projection_matrix;
  std::map<TexturedModel*, std::vector<Entity*>> entities;
  std::vector<Terrain*> terrains;

  int previous_terrain_grid_x = 0;
  int previous_terrain_grid_z = 0;
};

#endif // !MASTERRENDERER_H
