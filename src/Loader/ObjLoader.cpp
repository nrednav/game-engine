#include "ObjLoader.h"
#include <cstring>
#include <stdio.h>

RawModel* ObjLoader::load_model(std::string fileName, Loader* loader) {
  // Open the file as read only
  FILE* file = fopen(("assets/models/" + fileName + ".obj").c_str(), "r");

  if (!file) {
    printf("Failed to open: %s\n", fileName.c_str());
  }

  // Storage variables
  std::vector<float> vertices, texturesArray, normalsArray;
  std::vector<glm::vec2> textures;
  std::vector<glm::vec3> normals;
  std::vector<int> indices;

  char *type, *token, *stop = 0;
  char line[256];

  while (fgets(line, 256, file) != NULL) {
    token = NULL;
    type = strtok_r(line, " ", &token);

    // V is vertex points
    if (type[0] == 'v' && type[1] == NULL) {
      vertices.push_back(strtof(token, &stop));

      token = stop + 1; // Move to the next value

      vertices.push_back(strtof(token, &stop));

      token = stop + 1;

      vertices.push_back(strtof(token, &stop));
    }
    // VT is vertex texture coordinates
    else if (type[0] == 'v' && type[1] == 't') {
      double x = strtod(token, &stop);

      token = stop + 1;

      double y = strtod(token, &stop);

      textures.push_back(glm::vec2(x, y));
    }
    // VN is vertex normals
    else if (type[0] == 'v' && type[1] == 'n') {
      double x = strtod(token, &stop);

      token = stop + 1;

      double y = strtod(token, &stop);

      token = stop + 1;

      double z = strtod(token, &stop);

      normals.push_back(glm::vec3(x, y, z));
    }
    // F is the index list for faces
    else if (type[0] == 'f') {
      if (indices.size() == 0) {
        texturesArray.resize((vertices.size() / 3) * 2);
        normalsArray.resize(vertices.size());
      }

      process_vertices(token, indices, textures, texturesArray, normals,
                       normalsArray);
    }
  }

  fclose(file);

  return loader->load_to_vao(vertices, indices, texturesArray, normalsArray);
}

void ObjLoader::process_vertices(char* vertexData, std::vector<int>& indices,
                                 std::vector<glm::vec2>& textures,
                                 std::vector<float>& texturesArray,
                                 std::vector<glm::vec3>& normals,
                                 std::vector<float>& normalsArray) {
  char* stop;
  int vertexPointer;

  for (unsigned int i = 0; i < 3; i++) {
    // Get and store index
    vertexPointer = strtol(vertexData, &stop, 10) - 1;
    indices.push_back(vertexPointer);
    vertexData = stop + 1; // Move to the next value

    // Get and store texture points
    glm::vec2 texture = textures[strtol(vertexData, &stop, 10) - 1];
    texturesArray[vertexPointer * 2] = texture.x;
    texturesArray[vertexPointer * 2 + 1] = 1 - texture.y;
    vertexData = stop + 1; // Move to the next value

    // Get and store normal points
    glm::vec3 normal = normals[strtol(vertexData, &stop, 10) - 1];
    normalsArray[vertexPointer * 3] = normal.x;
    normalsArray[vertexPointer * 3 + 1] = normal.y;
    normalsArray[vertexPointer * 3 + 2] = normal.z;
    vertexData = stop + 1; // Move to the next value
  }
}
