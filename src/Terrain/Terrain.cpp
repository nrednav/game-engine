#include "Terrain.h"
#include "Utils/Math.h"
#include "Constants.h"
#include <vector>

Terrain::Terrain(
  float grid_x,
  float grid_z,
  Loader* loader,
  TerrainTexturePack* texture_pack,
  std::string height_map_filepath
) {
  this->texture_pack = texture_pack;
  this->x = grid_x * TERRAIN_SIZE;
  this->z = grid_z * TERRAIN_SIZE;
  this->model = generate_terrain(loader, height_map_filepath);
}

RawModel*
Terrain::generate_terrain(Loader* loader, std::string height_map_filepath) {
  int image_width, image_height, component_count;

  stbi_uc* image_data = stbi_load(
    height_map_filepath.c_str(),
    &image_width,
    &image_height,
    &component_count,
    STBI_rgb
  );

  int TERRAIN_VERTEX_COUNT = image_width;

  this->height_map = std::vector<std::vector<float>>(
    TERRAIN_VERTEX_COUNT,
    std::vector<float>(TERRAIN_VERTEX_COUNT, 0.0f)
  );

  int tile_count = TERRAIN_VERTEX_COUNT * TERRAIN_VERTEX_COUNT;
  int last_terrain_index = TERRAIN_VERTEX_COUNT - 1;

  std::vector<float> vertices(tile_count * 3);
  std::vector<float> normals(tile_count * 3);
  std::vector<float> texture_coords(tile_count * 2);
  std::vector<int> indices(6 * last_terrain_index * last_terrain_index);

  unsigned int vertex_pointer = 0;

  for (int i = 0; i < TERRAIN_VERTEX_COUNT; i++) {
    for (int j = 0; j < TERRAIN_VERTEX_COUNT; j++) {
      vertices[vertex_pointer * 3] =
        -(float)j / ((float)last_terrain_index) * TERRAIN_SIZE;

      float height = this->get_height(j, i, image_data, image_width);

      this->height_map[j][i] = height;

      vertices[vertex_pointer * 3 + 1] = height;
      vertices[vertex_pointer * 3 + 2] =
        -(float)i / ((float)last_terrain_index) * TERRAIN_SIZE;

      glm::vec3 normal = this->calculate_normal(j, i, image_data, image_width);
      normals[vertex_pointer * 3] = normal.x;
      normals[vertex_pointer * 3 + 1] = normal.y;
      normals[vertex_pointer * 3 + 2] = normal.z;

      texture_coords[vertex_pointer * 2] =
        (float)j / ((float)last_terrain_index);
      texture_coords[vertex_pointer * 2 + 1] =
        (float)i / ((float)last_terrain_index);

      vertex_pointer++;
    }
  }

  unsigned int pointer = 0;

  for (int grid_z = 0; grid_z < last_terrain_index; grid_z++) {
    for (int grid_x = 0; grid_x < last_terrain_index; grid_x++) {
      int top_left = (grid_z * TERRAIN_VERTEX_COUNT) + grid_x;
      int top_right = top_left + 1;
      int bottom_left = ((grid_z + 1) * TERRAIN_VERTEX_COUNT) + grid_x;
      int bottom_right = bottom_left + 1;

      indices[pointer++] = top_left;
      indices[pointer++] = bottom_left;
      indices[pointer++] = top_right;
      indices[pointer++] = top_right;
      indices[pointer++] = bottom_left;
      indices[pointer++] = bottom_right;
    }
  }

  return loader->load_to_vao(vertices, indices, texture_coords, normals);
}

float Terrain::get_height(
  const int& x,
  const int& z,
  stbi_uc* image_data,
  const int& image_width
) {
  if (x < 0 || x >= image_width || z < 0 || z >= image_width) {
    return 1.0f;
  }

  const stbi_uc* pixel = image_data + (3 * (z * image_width + x));

  int height = pixel[0];
  int input_range = 255 - 0;
  int output_range = (int)(TERRAIN_MAX_HEIGHT - TERRAIN_MIN_HEIGHT);

  float output = (height - 0) * output_range / input_range + TERRAIN_MIN_HEIGHT;

  return output;
}

glm::vec3 Terrain::calculate_normal(
  const int& x,
  const int& z,
  stbi_uc* image_data,
  const int& image_width
) {
  float height_l = this->get_height(x - 1, z, image_data, image_width);
  float height_r = this->get_height(x + 1, z, image_data, image_width);
  float height_u = this->get_height(x, z + 1, image_data, image_width);
  float height_d = this->get_height(x, z - 1, image_data, image_width);

  glm::vec3 normal = glm::vec3(height_l - height_r, 2.0f, height_d - height_u);

  return glm::normalize(normal);
}

float Terrain::get_terrain_height_at(float world_x, float world_z) {
  float terrain_x = world_x - this->x;
  float terrain_z = world_z - this->z;
  float grid_tile_size = -(TERRAIN_SIZE / ((float)this->height_map.size() - 1));

  int grid_x = (int)glm::floor(terrain_x / grid_tile_size);
  int grid_z = (int)glm::floor(terrain_z / grid_tile_size);

  bool x_out_of_bounds = grid_x >= this->height_map.size() - 1 || grid_x < 0;
  bool z_out_of_bounds = grid_z >= this->height_map.size() - 1 || grid_z < 0;

  if (x_out_of_bounds || z_out_of_bounds) {
    return 0.0f;
  }

  float x_coord = fmod(terrain_x, grid_tile_size) / grid_tile_size;
  float z_coord = fmod(terrain_z, grid_tile_size) / grid_tile_size;

  float terrain_height;

  if (x_coord <= (1 - z_coord)) {
    terrain_height = Math::get_barry_centric_coordinate(
      glm::vec3(0, this->height_map[grid_x][grid_z], 0),
      glm::vec3(1, this->height_map[grid_x + 1][grid_z], 0),
      glm::vec3(0, this->height_map[grid_x][grid_z + 1], 1),
      glm::vec2(x_coord, z_coord)
    );
  }
  else {
    terrain_height = Math::get_barry_centric_coordinate(
      glm::vec3(1, this->height_map[grid_x + 1][grid_z], 0),
      glm::vec3(1, this->height_map[grid_x + 1][grid_z + 1], 1),
      glm::vec3(0, this->height_map[grid_x][grid_z + 1], 1),
      glm::vec2(x_coord, z_coord)
    );
  }

  return terrain_height;
}
