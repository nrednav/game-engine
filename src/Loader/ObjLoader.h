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
  static RawModel* load_model(std::string filename, Loader* loader);

private:
  static void process_vertices(char* vertex_data, std::vector<int>& indices,
                               std::vector<glm::vec2>& textures,
                               std::vector<float>& textures_array,
                               std::vector<glm::vec3>& normals,
                               std::vector<float>& normals_array);
};

#endif // !OBJLOADER_H
