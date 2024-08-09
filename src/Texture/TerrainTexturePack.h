#ifndef TERRAINTEXTUREPACK_H
#define TERRAINTEXTUREPACK_H

#include "TerrainTexture.h"

class TerrainTexturePack {
public:
  TerrainTexturePack(
    TerrainTexture* bg_texture,
    TerrainTexture* r_texture,
    TerrainTexture* g_texture,
    TerrainTexture* b_texture
  ) {
    this->bg_texture = bg_texture;
    this->r_texture = r_texture;
    this->g_texture = g_texture;
    this->b_texture = b_texture;
  }

  TerrainTexture* get_background_texture() const { return this->bg_texture; }
  TerrainTexture* get_red_texture() const { return this->r_texture; }
  TerrainTexture* get_green_texture() const { return this->g_texture; }
  TerrainTexture* get_blue_texture() const { return this->b_texture; }

private:
  TerrainTexture* bg_texture;
  TerrainTexture* r_texture;
  TerrainTexture* g_texture;
  TerrainTexture* b_texture;
};

#endif // !TERRAINTEXTUREPACK_H
