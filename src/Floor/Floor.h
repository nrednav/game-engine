#ifndef FLOOR_H
#define FLOOR_H

#include "Terrain/Terrain.h"
#include "Texture/TerrainTexturePack.h"
#include <memory>

using TerrainGrid = std::vector<std::vector<std::unique_ptr<Terrain>>>;

struct FloorDimensions {
  unsigned int length;
  unsigned int width;
};

class Floor {
public:
  Floor(FloorDimensions dimensions, Loader* loader);
  ~Floor();

  Terrain* get_terrain_at(unsigned int row, unsigned int column);
  TerrainGrid& get_terrain_grid();

private:
  TerrainGrid terrain_grid{};
  std::unique_ptr<TerrainTexturePack> terrain_texture_pack{};
};

#endif // !FLOOR_H
