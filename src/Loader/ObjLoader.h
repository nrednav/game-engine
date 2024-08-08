#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "Loader.h"
#include "Model/RawModel.h"

#include <glm/glm.hpp>
#include <string>
#include <vector>

class ObjLoader {
public:
  ObjLoader() {}
  static RawModel* load_model(std::string fileName, Loader* loader);

private:
  static void process_vertices(char* vertexData, std::vector<int>& indices,
                               std::vector<glm::vec2>& textures,
                               std::vector<float>& texturesArray,
                               std::vector<glm::vec3>& normals,
                               std::vector<float>& normalsArray);
};

#endif // !OBJLOADER_H
