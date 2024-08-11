#include <cstdlib>
#include <memory>
#include <vector>
#include <iostream>

#include "Display/DisplayManager.h"
#include "Loader/Loader.h"
#include "Renderer/MasterRenderer.h"
#include "Entity/EntityManager.h"
#include "Constants.h"
#include "Texture/TerrainTexture.h"

int main() {
  try {
    DisplayManager::get_instance()->create_display();

    auto display_manager = DisplayManager::get_instance();
    auto display = display_manager->get_display();
    auto loader = std::make_unique<Loader>();
    auto renderer = std::make_unique<MasterRenderer>(loader.get());

    auto bg_texture_id = loader->load_texture("terrain/grass/2", true);
    auto r_texture_id = loader->load_texture("terrain/mud", true);
    auto g_texture_id = loader->load_texture("terrain/grass/flowers", true);
    auto b_texture_id = loader->load_texture("terrain/path", true);
    auto blend_map_texture_id = loader->load_texture("blend_map", true);

    auto bg_texture = std::make_unique<TerrainTexture>(bg_texture_id);
    auto r_texture = std::make_unique<TerrainTexture>(r_texture_id);
    auto g_texture = std::make_unique<TerrainTexture>(g_texture_id);
    auto b_texture = std::make_unique<TerrainTexture>(b_texture_id);
    auto blend_map_texture =
      std::make_unique<TerrainTexture>(blend_map_texture_id);

    auto terrain_texture_pack = std::make_unique<TerrainTexturePack>(
      bg_texture.get(),
      r_texture.get(),
      g_texture.get(),
      b_texture.get()
    );

    std::vector<std::vector<std::unique_ptr<Terrain>>> terrains;
    terrains.resize(2);
    for (auto& inner : terrains) {
      inner.resize(2);
    }

    terrains[0][0] = std::make_unique<Terrain>(
      0,
      0,
      loader.get(),
      terrain_texture_pack.get(),
      blend_map_texture.get(),
      "height_map"
    );

    terrains[0][1] = std::make_unique<Terrain>(
      0,
      1,
      loader.get(),
      terrain_texture_pack.get(),
      blend_map_texture.get(),
      "height_map"
    );

    terrains[1][0] = std::make_unique<Terrain>(
      1,
      0,
      loader.get(),
      terrain_texture_pack.get(),
      blend_map_texture.get(),
      "height_map"
    );

    terrains[1][1] = std::make_unique<Terrain>(
      1,
      1,
      loader.get(),
      terrain_texture_pack.get(),
      blend_map_texture.get(),
      "height_map"
    );

    auto entity_manager = EntityManager::get_instance();
    entity_manager->initialize(loader.get(), terrains[0][0].get());
    entity_manager->generate_entities(ENTITY_COUNT);

    auto player = entity_manager->create_player("player", 1.0f);
    auto camera = std::make_unique<Camera>(player, glm::vec3(0, 5, 0));

    int previous_grid_x = 0;
    int previous_grid_z = 0;

    while (!glfwWindowShouldClose(display)) {
      int current_grid_x = (int)(player->get_position().x / TERRAIN_SIZE + 1);
      int current_grid_z = (int)(player->get_position().z / TERRAIN_SIZE + 1);

      if (current_grid_x != previous_grid_x || current_grid_z != previous_grid_z) {
        previous_grid_x = current_grid_x;
        previous_grid_z = current_grid_z;
        entity_manager->recalculate_entity_positions(
          terrains[current_grid_x][current_grid_z].get()
        );
      }

      player->move(terrains[current_grid_x][current_grid_z].get());
      camera->move();

      renderer->render_scene(
        entity_manager->get_entities(),
        terrains,
        entity_manager->get_lights(),
        player,
        camera.get()
      );

      display_manager->update_display();
    }

    entity_manager->cleanup();
    renderer->cleanup();
    loader->cleanup();
    display_manager->close_display();
  }
  catch (const std::exception& exception) {
    std::cerr << exception.what() << std::endl;

    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
