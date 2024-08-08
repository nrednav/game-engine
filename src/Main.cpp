#include "Display/DisplayManager.h"
#include "Loader/Loader.h"
#include "Renderer/MasterRenderer.h"
#include "Entity/EntityManager.h"
#include "Constants.h"
#include <vector>
#include <iostream>

int main() {
  if (!DisplayManager::get_instance()->create_display()) {
    std::cout << "Failed to create window..." << std::endl;
    return -1;
  }

  GLFWwindow* display = DisplayManager::get_instance()->get_display();
  Loader* loader = new Loader();
  MasterRenderer* renderer = new MasterRenderer(loader);

  TerrainTexture* bgTexture =
      new TerrainTexture(loader->loadTexture("grassTerrain2", true));
  TerrainTexture* rTexture =
      new TerrainTexture(loader->loadTexture("mudTerrain", true));
  TerrainTexture* gTexture =
      new TerrainTexture(loader->loadTexture("grassFlowersTerrain", true));
  TerrainTexture* bTexture =
      new TerrainTexture(loader->loadTexture("pathTerrain", true));
  TerrainTexture* blendMap =
      new TerrainTexture(loader->loadTexture("blendMap", true));

  TerrainTexturePack* texturePack =
      new TerrainTexturePack(bgTexture, rTexture, gTexture, bTexture);

  std::vector<std::vector<Terrain*>> terrains(2, std::vector<Terrain*>(2));
  terrains[0][0] =
      new Terrain(0, 0, loader, texturePack, blendMap, "heightmap");
  terrains[0][1] =
      new Terrain(0, 1, loader, texturePack, blendMap, "heightmap");
  terrains[1][0] =
      new Terrain(1, 0, loader, texturePack, blendMap, "heightmap");
  terrains[1][1] =
      new Terrain(1, 1, loader, texturePack, blendMap, "heightmap");

  EntityManager* entityManager = EntityManager::get_instance();
  entityManager->initialize(loader, terrains[0][0]);
  entityManager->generate_entities(ENTITY_COUNT);

  Player* player = entityManager->create_player("player", 1.0f);
  Camera* camera = new Camera(player, glm::vec3(0, 5, 0));

  int previousGridX = 0, previousGridZ = 0;

  while (!glfwWindowShouldClose(display)) {
    int gridX = (int)(player->get_position().x / TERRAIN_SIZE + 1);
    int gridZ = (int)(player->get_position().z / TERRAIN_SIZE + 1);

    if (gridX != previousGridX || gridZ != previousGridZ) {
      previousGridX = gridX;
      previousGridZ = gridZ;
      entityManager->recalculate_entity_positions(terrains[gridX][gridZ]);
    }

    player->move(terrains[gridX][gridZ]);
    camera->move();

    renderer->renderScene(entityManager->get_entities(), terrains,
                          entityManager->get_lights(), player, camera);

    DisplayManager::get_instance()->update_display();
  }

  entityManager->cleanup();
  renderer->cleanup();
  loader->cleanup();
  DisplayManager::get_instance()->close_display();

  return 0;
}
