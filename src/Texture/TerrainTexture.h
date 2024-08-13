#ifndef TERRAINTEXTURE_H
#define TERRAINTEXTURE_H

#include "Loader/Loader.h"
#include <string>

struct TerrainTextureData {
  std::string filename;
  bool repeating;
};

class TerrainTexture {
public:
  TerrainTexture(TerrainTextureData data, Loader* loader);

  unsigned int get_id() const { return this->id; }

private:
  unsigned int id;
};

#endif // !TERRAINTEXTURE_H
