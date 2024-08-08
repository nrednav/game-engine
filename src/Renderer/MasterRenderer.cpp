#include "GL/glew.h"
#include "MasterRenderer.h"
#include "Constants.h"

MasterRenderer::MasterRenderer(Loader* loader) {
  this->enableCulling();
  this->entityShader = new StaticShader("src/Shader/vertexShader.txt",
                                        "src/Shader/fragmentShader.txt");
  this->createProjectionMatrix();
  this->entityRenderer =
      new EntityRenderer(this->entityShader, this->projectionMatrix);

  this->terrainShader =
      new TerrainShader("src/Shader/terrainVertexShader.txt",
                        "src/Shader/terrainFragmentShader.txt");
  this->terrainRenderer =
      new TerrainRenderer(this->terrainShader, this->projectionMatrix);

  this->skyboxShader = new SkyboxShader("src/Skybox/skyboxVertexShader.txt",
                                        "src/Skybox/skyboxFragmentShader.txt");
  this->skyboxRenderer =
      new SkyboxRenderer(this->skyboxShader, loader, this->projectionMatrix);
}

void MasterRenderer::prepare() {
  glEnable(GL_DEPTH_TEST);
  glClearColor(SKY_COLOR_R, SKY_COLOR_G, SKY_COLOR_B, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::render(std::vector<Light*> lights, Camera* camera) {
  prepare();

  glm::vec3 skyColor = glm::vec3(SKY_COLOR_R, SKY_COLOR_G, SKY_COLOR_B);

  // Entity rendering
  this->entityShader->start();
  this->entityShader->loadSkyColor(skyColor);
  this->entityShader->loadLights(lights);
  this->entityShader->loadViewMatrix(camera);
  this->entityRenderer->render(this->entities);
  this->entityShader->stop();

  // Terrain rendering
  this->terrainShader->start();
  this->terrainShader->loadSkyColor(skyColor);
  this->terrainShader->loadLights(lights);
  this->terrainShader->loadViewMatrix(camera);
  this->terrainRenderer->render(this->terrains);
  this->terrainShader->stop();

  // Skybox rendering
  this->skyboxRenderer->render(camera, skyColor);

  this->entities.clear();
  this->terrains.clear();
}

void MasterRenderer::renderScene(const std::vector<Entity*>& entities,
                                 std::vector<std::vector<Terrain*>>& terrains,
                                 const std::vector<Light*>& lights,
                                 Player* player, Camera* camera) {
  this->processEntity(player);

  for (int row = 0; row < terrains.size(); row++) {
    for (int col = 0; col < terrains[row].size(); col++) {
      this->processTerrain(terrains[row][col]);
    }
  }

  for (Entity* entity : entities) {
    this->processEntity(entity);
  }

  this->render(lights, camera);
}

void MasterRenderer::processEntity(Entity* entity) {
  TexturedModel* model = entity->getModel();
  std::vector<Entity*> batch = this->entities[model];

  if (batch.size() > 0) {
    this->entities[model].push_back(entity);
  } else {
    std::vector<Entity*> newBatch;
    newBatch.push_back(entity);
    this->entities[model] = newBatch;
  }
}

void MasterRenderer::processTerrain(Terrain* terrain) {
  this->terrains.push_back(terrain);
}

void MasterRenderer::createProjectionMatrix() {
  float aspectRatio = (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT;
  float yScale = (1.0f / glm::tan(glm::radians(FOV / 2.0f))) * aspectRatio;
  float xScale = yScale / aspectRatio;
  float frustumLength = FAR_PLANE - NEAR_PLANE;

  this->projectionMatrix = glm::mat4();
  this->projectionMatrix[0][0] = xScale;
  this->projectionMatrix[1][1] = yScale;
  this->projectionMatrix[2][2] = -((FAR_PLANE + NEAR_PLANE) / frustumLength);
  this->projectionMatrix[2][3] = -1;
  this->projectionMatrix[3][2] =
      -((2 * NEAR_PLANE * FAR_PLANE) / frustumLength);
  this->projectionMatrix[3][3] = 0;
}

void MasterRenderer::enableCulling() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

void MasterRenderer::disableCulling() { glDisable(GL_CULL_FACE); }

void MasterRenderer::cleanup() {
  this->entityShader->cleanup();
  this->terrainShader->cleanup();
}
