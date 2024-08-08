#include "OBJLoader.h"
#include <cstring>
#include <stdio.h>

RawModel* OBJLoader::loadModel_v2(std::string fileName, Loader* loader) {
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
      // Store a new vertex
      vertices.push_back(strtof(token, &stop));
      token = stop + 1; // Move to the next value
      vertices.push_back(strtof(token, &stop));
      token = stop + 1; // Move to the next value
      vertices.push_back(strtof(token, &stop));
    }
    // VT is vertex texture coordinates
    else if (type[0] == 'v' && type[1] == 't') {
      double x = strtod(token, &stop);
      token = stop + 1; // Move to the next value
      double y = strtod(token, &stop);
      // Store a new texture
      textures.push_back(glm::vec2(x, y));
    } else if (type[0] == 'v' && type[1] == 'n') {
      double x = strtod(token, &stop);
      token = stop + 1; // Move to the next value
      double y = strtod(token, &stop);
      token = stop + 1; // Move to the next value
      double z = strtod(token, &stop);
      // Store a new normal
      normals.push_back(glm::vec3(x, y, z));
    }
    // F is the index list for faces
    else if (type[0] == 'f') {
      if (indices.size() == 0) {
        // Set the size of the array
        texturesArray.resize((vertices.size() / 3) * 2);
        normalsArray.resize(vertices.size());
      }
      // Process set of vertex data
      processVertices_v2(token, indices, textures, texturesArray, normals,
                         normalsArray);
    }
  }
  fclose(file);

  return loader->loadToVAO(vertices, indices, texturesArray, normalsArray);
}

void OBJLoader::processVertices_v2(char* vertexData, std::vector<int>& indices,
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

// RawModel* OBJLoader::loadModel(std::string fileName, Loader* loader)
//{
//	std::string filePath = "assets/models/" + fileName + ".obj";
//	std::ifstream file(filePath);
//	std::string line, token;
//	char type;
//
//	std::vector<glm::vec2> textureCoords;
//	std::vector<glm::vec3> vertices, normals;
//	std::vector<int> indices;
//
//	std::vector<float> finalNormals, finalTextureCoords;
//
//	while (std::getline(file, line)) {
//		type = line.at(0);
//
//		if (type == 'v') {
//			if (line.at(1) == ' ') {
//				loadVertexPositions(vertices, line.substr(2,
// line.length() - 1));
//			}
//			else if (line.at(1) == 't') {
//				loadVertexTextureCoords(textureCoords,
// line.substr(3, line.length() - 1));
//			}
//			else if (line.at(1) == 'n') {
//				loadVertexNormals(normals, line.substr(3,
// line.length() - 1));
//			}
//		}
//		else if (type == 'f') {
//			if (indices.size() == 0) {
//				finalTextureCoords.resize(vertices.size() * 2);
//				finalNormals.resize(vertices.size() * 3);
//			}
//
//			processVertices(
//				vertices, textureCoords,
//				normals, indices,
//				finalTextureCoords, finalNormals,
//				line.substr(2, line.length() - 1)
//			);
//		}
//	}
//
//	std::vector<float> finalVertices(vertices.size() * 3);
//	std::vector<int> finalIndices(indices.size());
//
//	int vertexIndex = 0;
//	for (glm::vec3 vertex : vertices) {
//		finalVertices[vertexIndex++] = vertex.x;
//		finalVertices[vertexIndex++] = vertex.y;
//		finalVertices[vertexIndex++] = vertex.z;
//	}
//
//	for (unsigned int i = 0; i < indices.size(); i++) {
//		finalIndices[i] = indices.at(i);
//	}
//
//	return loader->loadToVAO(
//		finalVertices,
//		finalIndices,
//		finalTextureCoords
//	);
// }
//
// void OBJLoader::loadVertexPositions(std::vector<glm::vec3>& vertices,
// std::string line)
//{
//	std::stringstream ss(line);
//	std::string token;
//	std::vector<float> vertex;
//
//	while (std::getline(ss, token, ' ')) {
//		vertex.push_back(std::stof(token));
//	}
//
//	vertices.push_back(glm::vec3(vertex[0], vertex[1], vertex[2]));
// }
//
// void OBJLoader::loadVertexTextureCoords(std::vector<glm::vec2>&
// textureCoords, std::string line)
//{
//	std::stringstream ss(line);
//	std::string token;
//	std::vector<float> textureCoordinate;
//
//	while (std::getline(ss, token, ' ')) {
//		textureCoordinate.push_back(std::stof(token));
//	}
//
//	textureCoords.push_back(glm::vec2(textureCoordinate[0],
// textureCoordinate[1]));
// }
//
// void OBJLoader::loadVertexNormals(std::vector<glm::vec3>& normals,
// std::string line)
//{
//	std::stringstream ss(line);
//	std::string token;
//	std::vector<float> normal;
//
//	while (std::getline(ss, token, ' ')) {
//		normal.push_back(std::stof(token));
//	}
//
//	normals.push_back(glm::vec3(normal[0], normal[1], normal[2]));
// }
//
// void OBJLoader::processVertices(
//	std::vector<glm::vec3>& vertices,
//	std::vector<glm::vec2>& textureCoords,
//	std::vector<glm::vec3>& normals,
//	std::vector<int>& indices,
//	std::vector<float>& finalTextureCoords,
//	std::vector<float>& finalNormals,
//	std::string line
//) {
//	// line = a/b/c a/b/c a/b/c
//	std::stringstream ss(line);
//	std::string token;
//
//	while (std::getline(ss, token, ' ')) {
//		// token = a/b/c
//		std::regex reg("[0-9]+");
//		std::vector<int> triangleVertices;
//
//		std::sregex_iterator iter(token.begin(), token.end(), reg);
//		std::sregex_iterator end;
//
//		while (iter != end) {
//			for (unsigned int i = 0; i < iter->size(); i++) {
//				std::string index = (*iter)[i];
//				triangleVertices.push_back(std::stoi(index));
//			}
//			++iter;
//		}
//
//		int vertexIndex = triangleVertices[0] - 1;
//		indices.push_back(vertexIndex);
//
//		glm::vec2 currentTextureCoord =
// textureCoords.at(triangleVertices[1] - 1);
// finalTextureCoords[vertexIndex * 2] = currentTextureCoord.x;
// finalTextureCoords[vertexIndex * 2 + 1] = 1 - currentTextureCoord.y;
//
//		glm::vec3 currentNormal = normals.at(triangleVertices[2] - 1);
//		finalNormals[vertexIndex * 3] = currentNormal.x;
//		finalNormals[vertexIndex * 3 + 1] = currentNormal.y;
//		finalNormals[vertexIndex * 3 + 2] = currentNormal.z;
//	}
// }
