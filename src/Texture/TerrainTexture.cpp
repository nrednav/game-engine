#include "TerrainTexture.h"

TerrainTexture::TerrainTexture(TerrainTextureData data, Loader* loader) {
  this->id = loader->load_texture(data.filepath, data.repeating);
}
