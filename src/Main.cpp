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

  TerrainTexture* bg_texture =
    new TerrainTexture(loader->load_texture("terrain/grass/2", true));
  TerrainTexture* r_texture =
    new TerrainTexture(loader->load_texture("terrain/mud", true));
  TerrainTexture* g_texture =
    new TerrainTexture(loader->load_texture("terrain/grass/flowers", true));
  TerrainTexture* b_texture =
    new TerrainTexture(loader->load_texture("terrain/path", true));
  TerrainTexture* blend_map =
    new TerrainTexture(loader->load_texture("blend_map", true));

  TerrainTexturePack* texture_pack =
    new TerrainTexturePack(bg_texture, r_texture, g_texture, b_texture);

  std::vector<std::vector<Terrain*>> terrains(2, std::vector<Terrain*>(2));
  terrains[0][0] =
    new Terrain(0, 0, loader, texture_pack, blend_map, "height_map");
  terrains[0][1] =
    new Terrain(0, 1, loader, texture_pack, blend_map, "height_map");
  terrains[1][0] =
    new Terrain(1, 0, loader, texture_pack, blend_map, "height_map");
  terrains[1][1] =
    new Terrain(1, 1, loader, texture_pack, blend_map, "height_map");

  EntityManager* entity_manager = EntityManager::get_instance();
  entity_manager->initialize(loader, terrains[0][0]);
  entity_manager->generate_entities(ENTITY_COUNT);

  Player* player = entity_manager->create_player("player", 1.0f);
  Camera* camera = new Camera(player, glm::vec3(0, 5, 0));

  int previous_grid_x = 0, previous_grid_z = 0;

  while (!glfwWindowShouldClose(display)) {
    int grid_x = (int)(player->get_position().x / TERRAIN_SIZE + 1);
    int grid_z = (int)(player->get_position().z / TERRAIN_SIZE + 1);

    if (grid_x != previous_grid_x || grid_z != previous_grid_z) {
      previous_grid_x = grid_x;
      previous_grid_z = grid_z;
      entity_manager->recalculate_entity_positions(terrains[grid_x][grid_z]);
    }

    player->move(terrains[grid_x][grid_z]);
    camera->move();

    renderer->render_scene(
      entity_manager->get_entities(),
      terrains,
      entity_manager->get_lights(),
      player,
      camera
    );

    DisplayManager::get_instance()->update_display();
  }

  entity_manager->cleanup();
  renderer->cleanup();
  loader->cleanup();
  DisplayManager::get_instance()->close_display();

  return 0;
}
