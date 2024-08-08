#ifndef LOADER_H
#define LOADER_H

#include "Model/RawModel.h"
#include "Texture/TextureData.h"

#include <vector>
#include <string>

class Loader {
public:
  Loader() {}

  RawModel* loadToVAO(std::vector<float>& positions, std::vector<int>& indices,
                      std::vector<float>& textureCoords,
                      std::vector<float>& normals);
  RawModel* loadToVAO(std::vector<float>& positions, int dimensions);
  int loadTexture(std::string fileName, bool repeat = false);
  int loadCubeMap(std::vector<std::string>& textureFiles);

  void cleanup();

private:
  std::vector<unsigned int> vaoList;
  std::vector<unsigned int> vboList;
  std::vector<unsigned int> textures;

  unsigned int createVAO();
  void unbindVAO();
  void storeDataInAttributeList(int attributeID, int componentCount,
                                std::vector<float>& data);
  void bindIndicesBuffer(std::vector<int>& indices);
  TextureData* decodeTextureFile(std::string fileName);
};

#endif // !LOADER_H
