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
  Terrain(float gridX, float gridZ, Loader *loader,
          TerrainTexturePack *texturePack, TerrainTexture *blendMap,
          std::string heightMapFilename);
  RawModel *generateTerrain(Loader *loader, std::string heightMap);
  float getTerrainHeightAt(float worldX, float worldZ);

  float getX() const { return this->x; }
  float getZ() const { return this->z; }
  RawModel *getModel() const { return this->model; }
  TerrainTexturePack *getTexturePack() const { return this->texturePack; }
  TerrainTexture *getBlendMap() const { return this->blendMap; }

  void setX(float value) { this->x = value; }
  void setZ(float value) { this->z = value; }
  void setModel(RawModel *model) { this->model = model; }

private:
  float x;
  float z;

  RawModel *model;
  TerrainTexturePack *texturePack;
  TerrainTexture *blendMap;

  std::vector<std::vector<float>> heightMap;

  float getHeight(const int &x, const int &z, stbi_uc *imageData,
                  const int &imageWidth);
  glm::vec3 calculateNormal(const int &x, const int &z, stbi_uc *imageData,
                            const int &imageWidth);
};

#endif // !TERRAIN_H
