#include "GL/glew.h"
#include "Loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

RawModel* Loader::loadToVAO(std::vector<float>& positions,
                            std::vector<int>& indices,
                            std::vector<float>& textureCoords,
                            std::vector<float>& normals) {
  unsigned int vaoID = createVAO();
  bindIndicesBuffer(indices);
  storeDataInAttributeList(0, 3, positions);
  storeDataInAttributeList(1, 2, textureCoords);
  storeDataInAttributeList(2, 3, normals);
  unbindVAO();
  return new RawModel(vaoID, (unsigned int)indices.size());
}

RawModel* Loader::loadToVAO(std::vector<float>& positions, int dimensions) {
  int vaoID = createVAO();
  storeDataInAttributeList(0, dimensions, positions);
  unbindVAO();
  return new RawModel(vaoID, ((unsigned int)positions.size()) / dimensions);
}

unsigned int Loader::createVAO() {
  unsigned int vaoID;
  glGenVertexArrays(1, &vaoID);
  vaoList.push_back(vaoID);
  glBindVertexArray(vaoID);
  return vaoID;
}

void Loader::storeDataInAttributeList(int attributeNumber, int componentCount,
                                      std::vector<float>& data) {
  unsigned int vboID;
  glGenBuffers(1, &vboID);
  vboList.push_back(vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0],
               GL_STATIC_DRAW);
  glVertexAttribPointer(attributeNumber, componentCount, GL_FLOAT, false, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(std::vector<int>& indices) {
  unsigned int vboID;
  glGenBuffers(1, &vboID);
  vboList.push_back(vboID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int),
               &indices[0], GL_STATIC_DRAW);
}

int Loader::loadTexture(std::string fileName, bool repeat) {
  unsigned int textureID;
  int width, height, componentCount;
  std::string filePath = "assets/textures/" + fileName + ".png";
  stbi_uc* imageData =
      stbi_load(filePath.c_str(), &width, &height, &componentCount, 4);

  if (imageData == nullptr) {
    std::cout << "Failed to load texture: " << fileName << std::endl;
  }

  glGenTextures(1, &textureID);
  textures.push_back(textureID);

  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  if (!repeat) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, imageData);
  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.5f);

  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(imageData);

  return textureID;
}

int Loader::loadCubeMap(std::vector<std::string>& textureFiles) {
  unsigned int textureID;
  glGenTextures(1, &textureID);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

  for (int i = 0; i < textureFiles.size(); i++) {
    TextureData* data = this->decodeTextureFile(textureFiles[i]);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
                 data->getWidth(), data->getHeight(), 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data->getBuffer());
    stbi_image_free(data->getBuffer());
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  this->textures.push_back(textureID);

  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

  return textureID;
}

TextureData* Loader::decodeTextureFile(std::string fileName) {
  int width, height, nComponents;
  std::string filePath = "assets/textures/" + fileName + ".png";
  stbi_uc* imageData = stbi_load(filePath.c_str(), &width, &height,
                                 &nComponents, STBI_rgb_alpha);

  return new TextureData(imageData, width, height);
}

void Loader::unbindVAO() { glBindVertexArray(0); }

void Loader::cleanup() {
  for (unsigned int vaoID : vaoList)
    glDeleteVertexArrays(1, &vaoID);

  for (unsigned int vboID : vboList)
    glDeleteBuffers(1, &vboID);

  for (unsigned int textureID : textures)
    glDeleteTextures(1, &textureID);
}
