#include "GL/glew.h"
#include "MasterRenderer.h"
#include "Constants.h"
#include "Terrain/Terrain.h"
#include <memory>

MasterRenderer::MasterRenderer(Display* display, Loader* loader) {
  this->enable_culling();

  this->entity_shader = std::make_unique<StaticShader>(
    "src/Shader/EntityVertexShader.txt",
    "src/Shader/EntityFragmentShader.txt"
  );

  this->create_projection_matrix();

  this->entity_renderer = std::make_unique<EntityRenderer>(
    this->entity_shader.get(),
    this->projection_matrix
  );

  this->terrain_shader = std::make_unique<TerrainShader>(
    "src/Shader/TerrainVertexShader.txt",
    "src/Shader/TerrainFragmentShader.txt"
  );

  this->terrain_renderer = std::make_unique<TerrainRenderer>(
    this->terrain_shader.get(),
    this->projection_matrix
  );

  this->skybox_shader = std::make_unique<SkyboxShader>(
    "src/Skybox/SkyboxVertexShader.txt",
    "src/Skybox/SkyboxFragmentShader.txt",
    display
  );

  this->skybox_renderer = std::make_unique<SkyboxRenderer>(
    this->skybox_shader.get(),
    loader,
    this->projection_matrix,
    display
  );
}

MasterRenderer::~MasterRenderer() {
  this->entity_shader->cleanup();
  this->terrain_shader->cleanup();
}

void MasterRenderer::prepare() {
  glEnable(GL_DEPTH_TEST);
  glClearColor(SKY_COLOR_R, SKY_COLOR_G, SKY_COLOR_B, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::render(
  const std::vector<std::unique_ptr<Light>>& lights,
  Camera* camera
) {
  prepare();

  glm::vec3 sky_color = glm::vec3(SKY_COLOR_R, SKY_COLOR_G, SKY_COLOR_B);

  // Entity rendering
  this->entity_shader->start();
  this->entity_shader->load_sky_color(sky_color);
  this->entity_shader->load_lights(lights);
  this->entity_shader->load_view_matrix(camera);
  this->entity_renderer->render(this->entities);
  this->entity_shader->stop();

  // Terrain rendering
  this->terrain_shader->start();
  this->terrain_shader->load_sky_color(sky_color);
  this->terrain_shader->load_lights(lights);
  this->terrain_shader->load_view_matrix(camera);
  this->terrain_renderer->render(this->terrains);
  this->terrain_shader->stop();

  // Skybox rendering
  this->skybox_renderer->render(camera, sky_color);

  this->entities.clear();
  this->terrains.clear();
}

void MasterRenderer::render_scene(
  const std::vector<std::unique_ptr<Entity>>& entities,
  TerrainGrid& terrain_grid,
  const std::vector<std::unique_ptr<Light>>& lights,
  Player* player,
  Camera* camera
) {
  this->process_entity(player);

  for (int row = 0; row < terrain_grid.size(); row++) {
    for (int col = 0; col < terrain_grid[row].size(); col++) {
      this->process_terrain(terrain_grid[row][col].get());
    }
  }

  for (const auto& entity : entities) {
    this->process_entity(entity.get());
  }

  this->render(lights, camera);
}

void MasterRenderer::process_entity(Entity* entity) {
  TexturedModel* model = entity->get_model();
  std::vector<Entity*> batch = this->entities[model];

  if (batch.size() > 0) {
    this->entities[model].push_back(entity);
  }
  else {
    std::vector<Entity*> newBatch;
    newBatch.push_back(entity);
    this->entities[model] = newBatch;
  }
}

void MasterRenderer::process_terrain(Terrain* terrain) {
  this->terrains.push_back(terrain);
}

void MasterRenderer::create_projection_matrix() {
  float aspect_ratio = (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT;
  float y_scale = (1.0f / glm::tan(glm::radians(FOV / 2.0f))) * aspect_ratio;
  float x_scale = y_scale / aspect_ratio;
  float frustum_length = FAR_PLANE - NEAR_PLANE;

  this->projection_matrix = glm::mat4();
  this->projection_matrix[0][0] = x_scale;
  this->projection_matrix[1][1] = y_scale;
  this->projection_matrix[2][2] = -((FAR_PLANE + NEAR_PLANE) / frustum_length);
  this->projection_matrix[2][3] = -1;
  this->projection_matrix[3][2] =
    -((2 * NEAR_PLANE * FAR_PLANE) / frustum_length);
  this->projection_matrix[3][3] = 0;
}

void MasterRenderer::enable_culling() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

void MasterRenderer::disable_culling() {
  glDisable(GL_CULL_FACE);
}
