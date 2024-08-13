#ifndef TERRAINTEXTUREPACK_H
#define TERRAINTEXTUREPACK_H

#include "TerrainTexture.h"
#include <memory>
#include <unordered_map>

using TerrainTextureMap = std::unordered_map<std::string, TerrainTextureData>;

class TerrainTexturePack {
public:
  TerrainTexturePack(TerrainTextureMap texture_map, Loader* loader);

  TerrainTexture* get_background_texture() const {
    return this->background_texture.get();
  }
  TerrainTexture* get_red_texture() const { return this->red_texture.get(); }
  TerrainTexture* get_green_texture() const {
    return this->green_texture.get();
  }
  TerrainTexture* get_blue_texture() const { return this->blue_texture.get(); }
  TerrainTexture* get_blend_map_texture() const {
    return this->blend_map_texture.get();
  }

private:
  std::unique_ptr<TerrainTexture> background_texture;
  std::unique_ptr<TerrainTexture> red_texture;
  std::unique_ptr<TerrainTexture> green_texture;
  std::unique_ptr<TerrainTexture> blue_texture;
  std::unique_ptr<TerrainTexture> blend_map_texture;
};

#endif // !TERRAINTEXTUREPACK_H
