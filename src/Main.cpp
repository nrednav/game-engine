#include <cstdlib>
#include <memory>
#include <iostream>
#include "Display/Display.h"
#include "Loader/Loader.h"
#include "Renderer/MasterRenderer.h"
#include "Entity/EntityManager.h"
#include "Constants.h"
#include "Floor/Floor.h"

int main() {
  try {
    auto display = std::make_unique<Display>();
    auto loader = std::make_unique<Loader>();
    auto renderer =
      std::make_unique<MasterRenderer>(display.get(), loader.get());

    auto floor = std::make_unique<Floor>(
      FloorDimensions{.length = 2, .width = 2},
      loader.get()
    );

    auto entity_manager = std::make_unique<EntityManager>(
      loader.get(),
      floor->get_terrain_at(0, 0)
    );

    entity_manager->generate_entities(ENTITY_COUNT);

    auto player = entity_manager->create_player("player", 1.0f);
    auto camera = std::make_unique<Camera>(player.get(), glm::vec3(0, 5, 0));

    int previous_grid_x = 0;
    int previous_grid_z = 0;

    while (!glfwWindowShouldClose(display->get_window())) {
      int current_grid_x = (int)(player->get_position().x / TERRAIN_SIZE + 1);
      int current_grid_z = (int)(player->get_position().z / TERRAIN_SIZE + 1);

      auto current_terrain =
        floor->get_terrain_at(current_grid_x, current_grid_z);

      if (current_grid_x != previous_grid_x || current_grid_z != previous_grid_z) {
        previous_grid_x = current_grid_x;
        previous_grid_z = current_grid_z;
        entity_manager->recalculate_entity_positions(current_terrain);
      }

      player->move(current_terrain, display->get_frame_time_seconds());
      camera->move();

      renderer->render_scene(
        entity_manager->get_entities(),
        floor->get_terrain_grid(),
        entity_manager->get_lights(),
        player.get(),
        camera.get()
      );

      display->update();
    }
  }
  catch (const std::exception& exception) {
    std::cerr << exception.what() << std::endl;

    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
