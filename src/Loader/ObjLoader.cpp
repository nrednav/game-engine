#include "ObjLoader.h"
#include <cstring>
#include <stdio.h>

std::unique_ptr<RawModel>
ObjLoader::load_model(std::string filename, Loader* loader) {
  // Open the file as read only
  FILE* file = fopen(("assets/models/" + filename + ".obj").c_str(), "r");

  if (!file) {
    printf("Failed to open: %s\n", filename.c_str());
  }

  // Storage variables
  std::vector<float> vertices, textures_array, normals_array;
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
        textures_array.resize((vertices.size() / 3) * 2);
        normals_array.resize(vertices.size());
      }

      process_vertices(
        token,
        indices,
        textures,
        textures_array,
        normals,
        normals_array
      );
    }
  }

  fclose(file);

  return loader->load_to_vao(vertices, indices, textures_array, normals_array);
}

void ObjLoader::process_vertices(
  char* vertex_data,
  std::vector<int>& indices,
  std::vector<glm::vec2>& textures,
  std::vector<float>& textures_array,
  std::vector<glm::vec3>& normals,
  std::vector<float>& normals_array
) {
  char* stop;
  int vertex_pointer;

  for (unsigned int i = 0; i < 3; i++) {
    // Get and store index
    vertex_pointer = strtol(vertex_data, &stop, 10) - 1;
    indices.push_back(vertex_pointer);
    vertex_data = stop + 1;

    // Get and store texture points
    glm::vec2 texture = textures[strtol(vertex_data, &stop, 10) - 1];
    textures_array[vertex_pointer * 2] = texture.x;
    textures_array[vertex_pointer * 2 + 1] = 1 - texture.y;
    vertex_data = stop + 1;

    // Get and store normal points
    glm::vec3 normal = normals[strtol(vertex_data, &stop, 10) - 1];
    normals_array[vertex_pointer * 3] = normal.x;
    normals_array[vertex_pointer * 3 + 1] = normal.y;
    normals_array[vertex_pointer * 3 + 2] = normal.z;
    vertex_data = stop + 1;
  }
}
