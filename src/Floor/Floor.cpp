#include "Floor.h"

Floor::Floor(FloorDimensions dimensions, Loader* loader) {
  std::unordered_map<std::string, TerrainTextureData> terrain_texture_map{
    {"background",
     {
       .filepath = "assets/textures/terrain/grass/2.png",
       .repeating = true,
     }},
    {"red",
     {
       .filepath = "assets/textures/terrain/mud.png",
       .repeating = true,
     }},
    {"green",
     {
       .filepath = "assets/textures/terrain/grass/flowers.png",
       .repeating = true,
     }},
    {"blue",
     {
       .filepath = "assets/textures/terrain/path.png",
       .repeating = true,
     }},
    {"blend_map",
     {
       .filepath = "assets/textures/blend_map.png",
       .repeating = true,
     }},
  };

  this->terrain_texture_pack =
    std::make_unique<TerrainTexturePack>(terrain_texture_map, loader);

  this->terrain_grid.resize(dimensions.width);

  // Row = X-axis = Width, Column = Z-axis = Length
  for (auto& terrain_grid_column : this->terrain_grid) {
    terrain_grid_column.resize(dimensions.length);
  }

  for (int row = 0; row < dimensions.width; row++) {
    for (int column = 0; column < dimensions.length; column++) {
      auto terrain = std::make_unique<Terrain>(
        row,
        column,
        loader,
        this->terrain_texture_pack.get(),
        "assets/textures/height_map.png"
      );

      this->terrain_grid[row][column] = std::move(terrain);
    }
  }
}

Floor::~Floor() {}

Terrain* Floor::get_terrain_at(unsigned int row, unsigned int column) {
  return this->terrain_grid[row][column].get();
}

TerrainGrid& Floor::get_terrain_grid() {
  return this->terrain_grid;
}
