#include "TerrainTexturePack.h"

TerrainTexturePack::TerrainTexturePack(
  TerrainTextureMap texture_map,
  Loader* loader
) {
  this->background_texture =
    std::make_unique<TerrainTexture>(texture_map["background"], loader);
  this->red_texture =
    std::make_unique<TerrainTexture>(texture_map["red"], loader);
  this->green_texture =
    std::make_unique<TerrainTexture>(texture_map["green"], loader);
  this->blue_texture =
    std::make_unique<TerrainTexture>(texture_map["blue"], loader);
  this->blend_map_texture =
    std::make_unique<TerrainTexture>(texture_map["blend_map"], loader);
}
