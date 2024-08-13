#ifndef TERRAIN_H
#define TERRAIN_H

#include "Loader/Loader.h"
#include "Model/RawModel.h"
#include "Texture/TerrainTexturePack.h"
#include "glm/glm.hpp"
#include "stb_image.h"
#include <string>

class Terrain {
public:
  Terrain(
    float grid_x,
    float grid_z,
    Loader* loader,
    TerrainTexturePack* texture_pack,
    std::string height_map_filename
  );

  RawModel* generate_terrain(Loader* loader, std::string height_map);
  float get_terrain_height_at(float world_x, float world_z);

  float get_x() const { return this->x; }
  float get_z() const { return this->z; }
  RawModel* get_model() const { return this->model; }
  TerrainTexturePack* get_texture_pack() const { return this->texture_pack; }

  void set_x(float value) { this->x = value; }
  void set_z(float value) { this->z = value; }
  void setModel(RawModel* model) { this->model = model; }

private:
  float x;
  float z;

  RawModel* model;
  TerrainTexturePack* texture_pack;
  TerrainTexture* blend_map;
  std::vector<std::vector<float>> height_map;

  float get_height(
    const int& x,
    const int& z,
    stbi_uc* image_data,
    const int& image_width
  );

  glm::vec3 calculate_normal(
    const int& x,
    const int& z,
    stbi_uc* image_data,
    const int& image_width
  );
};

#endif // !TERRAIN_H
