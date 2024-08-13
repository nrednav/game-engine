#include "EntityManager.h"
#include "Loader/ObjLoader.h"
#include "Utils/RNG.h"

EntityManager::EntityManager(Loader* loader, Terrain* initial_terrain) {
  this->loader = loader;
  this->active_terrain = initial_terrain;
  this->load_entity_models();
}

EntityManager::~EntityManager() {
  this->loader = nullptr;
  this->active_terrain = nullptr;
  this->entities.clear();
  this->models.clear();
}

void EntityManager::generate_entities(int count) {
  this->create_lights();

  for (int i = 0; i < count; i++) {
    if (i % 10 == 0) {
      this->create_entity("grass", 0.9f);
      this->create_entity("flower", 2.3f);
      this->create_entity("fern", 0.9f);
    }

    if (i % 5 == 0) {
      float tree_scale = RNG::random_float() * 4 + 1;
      this->create_entity("pine", tree_scale);
      this->create_entity("low_poly_tree", tree_scale);
    }
  }
}

void EntityManager::load_entity_models() {
  // Objects
  this->models["player"] = this->create_textured_model("player", loader);
  this->models["lamp"] =
    this->create_textured_model("lamp", loader, false, true);

  // Environment
  this->models["pine"] = this->create_textured_model("pine", loader);
  this->models["low_poly_tree"] =
    this->create_textured_model("low_poly_tree", loader);
  this->models["grass"] =
    this->create_textured_model("grass", loader, true, true);
  this->models["flower"] =
    this->create_textured_model("flower", loader, true, true);
  this->models["fern"] =
    this->create_textured_model("fern", loader, true, false, true, 2);
}

void EntityManager::recalculate_entity_positions(Terrain* current_terrain) {
  for (unsigned int i = 0; i < this->entities.size(); i++) {
    float x = this->entities[i]->get_position().x;
    float z = this->entities[i]->get_position().z;
    float y = current_terrain->get_terrain_height_at(x, z);

    this->entities[i]->set_position(glm::vec3(x, y, z));
  }
}

Player* EntityManager::create_player(std::string name, float scale_factor) {
  glm::vec3 position;

  position.x = RNG::random_float() * 800 - 400;
  position.z = RNG::random_float() * -600;
  position.y =
    this->active_terrain->get_terrain_height_at(position.x, position.z);

  glm::vec3 rotation = glm::vec3(0, 0, 0);
  glm::vec3 scale = glm::vec3(scale_factor, scale_factor, scale_factor);

  return new Player(this->models[name], position, rotation, scale);
}

void EntityManager::create_entity(
  std::string name,
  float scale_factor,
  bool duplicate
) {
  TexturedModel* model = this->models[name];

  glm::vec3 position;
  position.x = RNG::random_float() * 800 - 400;
  position.z = RNG::random_float() * -600;
  position.y =
    this->active_terrain->get_terrain_height_at(position.x, position.z);

  glm::vec3 rotation = glm::vec3(0, RNG::random_float() * 360, 0);
  glm::vec3 scale = glm::vec3(scale_factor, scale_factor, scale_factor);

  if (model->get_texture()->get_row_count() > 1) {
    this->entities.push_back(
      new Entity(model, position, rotation, scale, RNG::random_int(4))
    );
  }
  else {
    this->entities.push_back(new Entity(model, position, rotation, scale));
  }

  if (duplicate) {
    Entity* lastEntity = this->entities[this->entities.size() - 1];

    float x = -(lastEntity->get_position().x);
    float z = -(lastEntity->get_position().z);
    float y = this->active_terrain->get_terrain_height_at(x, z);

    Entity* duplicate = new Entity(
      lastEntity->get_model(),
      glm::vec3(x, y, z),
      lastEntity->get_rotation(),
      lastEntity->get_scale()
    );

    this->entities.push_back(duplicate);
  }
}

TexturedModel* EntityManager::create_textured_model(
  std::string name,
  Loader* loader,
  bool has_transparency,
  bool uses_fake_lighting,
  bool uses_texture_atlas,
  int atlas_row_count
) {

  RawModel* entity_raw_model = ObjLoader::load_model(name, loader);
  ModelTexture* entity_texture =
    new ModelTexture(loader->load_texture("assets/textures/" + name + ".png"));

  if (uses_texture_atlas) {
    entity_texture->set_row_count(atlas_row_count);
  }

  TexturedModel* entity_textured_model =
    new TexturedModel(entity_raw_model, entity_texture);

  if (has_transparency) {
    entity_textured_model->get_texture()->set_transparency(true);
  }

  if (uses_fake_lighting) {
    entity_textured_model->get_texture()->use_fake_lighting(true);
  }

  return entity_textured_model;
}

void EntityManager::create_lights() {
  Light* sun = new Light(glm::vec3(0, 1000, 0), glm::vec3(1, 1, 1));

  this->create_entity("lamp", 1.0f, false);

  Entity* lamp = this->entities[this->entities.size() - 1];

  glm::vec3 position = lamp->get_position();
  position.y += 12.0f;

  glm::vec3 color = glm::vec3(2, 2, 0);
  glm::vec3 attenuation = glm::vec3(1, 0.01f, 0.002f);

  this->lights.push_back(sun);
  this->lights.push_back(new Light(position, color, attenuation));
}
