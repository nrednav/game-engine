#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Loader/Loader.h"
#include "Terrain/Terrain.h"
#include "Entity/Entity.h"
#include "Entity/Light.h"
#include "Entity/Player.h"
#include <memory>
#include <vector>
#include <map>
#include <string>

class EntityManager {
public:
  EntityManager(Loader* loader, Terrain* initial_terrain);
  ~EntityManager();

  std::unique_ptr<Player> create_player(std::string name, float scale_factor);

  void generate_entities(int count);
  void load_entity_models();
  void recalculate_entity_positions(Terrain* current_terrain);

  // Getters
  const std::vector<std::unique_ptr<Entity>>& get_entities() const {
    return this->entities;
  }

  const std::vector<std::unique_ptr<Light>>& get_lights() const {
    return this->lights;
  }

private:
  Loader* loader;
  Terrain* active_terrain;

  std::vector<std::unique_ptr<Entity>> entities;
  std::map<std::string, std::unique_ptr<TexturedModel>> models;
  std::vector<std::unique_ptr<Light>> lights;

  void create_entity(std::string name, float scale, bool duplicate = true);

  std::unique_ptr<TexturedModel> create_textured_model(
    std::string name,
    Loader* loader,
    bool has_transparency = false,
    bool uses_fake_lighting = false,
    bool uses_texture_atlas = false,
    int atlas_row_count = 1
  );

  void create_lights();
};

#endif // !ENTITYMANAGER_H
