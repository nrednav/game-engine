#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "Loader.h"
#include "Model/RawModel.h"
#include "glm/glm.hpp"

#include <string>
#include <vector>

class OBJLoader {
public:
  OBJLoader() {}
  // static RawModel* loadModel(std::string fileName, Loader* loader);
  static RawModel *loadModel_v2(std::string fileName, Loader *loader);

private:
  // static void loadVertexPositions(std::vector<glm::vec3>& vertices,
  // std::string line); static void
  // loadVertexTextureCoords(std::vector<glm::vec2>& textureCoords, std::string
  // line); static void loadVertexNormals(std::vector<glm::vec3>& normals,
  // std::string line); static void processVertices( 	std::vector<glm::vec3>&
  // vertices, 	std::vector<glm::vec2>& textureCoords, 	std::vector<glm::vec3>&
  // normals, 	std::vector<int>& indices, 	std::vector<float>&
  // finalTextureCoordinates, 	std::vector<float>& finalNormals,
  // std::string line
  //);
  static void processVertices_v2(char *vertexData, std::vector<int> &indices,
                                 std::vector<glm::vec2> &textures,
                                 std::vector<float> &texturesArray,
                                 std::vector<glm::vec3> &normals,
                                 std::vector<float> &normalsArray);
};

#endif // !OBJLOADER_H
