#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Loader/Loader.h"
#include "Terrain/Terrain.h"
#include "Entity/Entity.h"
#include "Entity/Light.h"
#include "Entity/Player.h"
#include <vector>
#include <map>
#include <string>

class EntityManager {
public:
  EntityManager(Loader* loader, Terrain* initial_terrain);
  ~EntityManager();

  Player* create_player(std::string name, float scale_factor);

  void generate_entities(int count);
  void load_entity_models();
  void recalculate_entity_positions(Terrain* current_terrain);
  void cleanup();

  // Getters
  std::vector<Entity*> get_entities() const { return this->entities; }
  std::vector<Light*> get_lights() const { return this->lights; }

private:
  Loader* loader;
  Terrain* active_terrain;

  std::vector<Entity*> entities;
  std::map<std::string, TexturedModel*> models;
  std::vector<Light*> lights;

  void create_entity(std::string name, float scale, bool duplicate = true);

  TexturedModel* create_textured_model(
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
