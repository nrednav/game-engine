#include "GL/glew.h"
#include "Loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

RawModel* Loader::load_to_vao(std::vector<float>& positions,
                              std::vector<int>& indices,
                              std::vector<float>& texture_coords,
                              std::vector<float>& normals) {
  unsigned int vao_id = create_vao();

  bind_indices_buffer(indices);
  store_data_in_attribute_list(0, 3, positions);
  store_data_in_attribute_list(1, 2, texture_coords);
  store_data_in_attribute_list(2, 3, normals);

  unbind_vao();

  return new RawModel(vao_id, (unsigned int)indices.size());
}

RawModel* Loader::load_to_vao(std::vector<float>& positions, int dimensions) {
  int vao_id = create_vao();

  store_data_in_attribute_list(0, dimensions, positions);
  unbind_vao();

  return new RawModel(vao_id, ((unsigned int)positions.size()) / dimensions);
}

unsigned int Loader::create_vao() {
  unsigned int vao_id;

  glGenVertexArrays(1, &vao_id);

  vao_list.push_back(vao_id);

  glBindVertexArray(vao_id);

  return vao_id;
}

void Loader::store_data_in_attribute_list(int attribute_number,
                                          int component_count,
                                          std::vector<float>& data) {
  unsigned int vbo_id;

  glGenBuffers(1, &vbo_id);

  vbo_list.push_back(vbo_id);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0],
               GL_STATIC_DRAW);
  glVertexAttribPointer(attribute_number, component_count, GL_FLOAT, false, 0,
                        0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bind_indices_buffer(std::vector<int>& indices) {
  unsigned int vbo_id;

  glGenBuffers(1, &vbo_id);

  vbo_list.push_back(vbo_id);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int),
               &indices[0], GL_STATIC_DRAW);
}

int Loader::load_texture(std::string filename, bool repeat) {
  unsigned int texture_id;
  int width, height, component_count;
  std::string filepath = "assets/textures/" + filename + ".png";
  stbi_uc* image_data =
      stbi_load(filepath.c_str(), &width, &height, &component_count, 4);

  if (image_data == nullptr) {
    std::cout << "Failed to load texture: " << filename << std::endl;
  }

  glGenTextures(1, &texture_id);
  textures.push_back(texture_id);

  glBindTexture(GL_TEXTURE_2D, texture_id);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  if (!repeat) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, image_data);
  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.5f);

  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(image_data);

  return texture_id;
}

int Loader::load_cube_map(std::vector<std::string>& texture_files) {
  unsigned int texture_id;

  glGenTextures(1, &texture_id);

  glActiveTexture(GL_TEXTURE0);

  glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

  for (int i = 0; i < texture_files.size(); i++) {
    TextureData* data = this->decode_texture_file(texture_files[i]);

    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
                 data->getWidth(), data->getHeight(), 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data->getBuffer());

    stbi_image_free(data->getBuffer());
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  this->textures.push_back(texture_id);

  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

  return texture_id;
}

TextureData* Loader::decode_texture_file(std::string filename) {
  int width, height, component_count;

  std::string filepath = "assets/textures/" + filename + ".png";
  stbi_uc* image_data = stbi_load(filepath.c_str(), &width, &height,
                                  &component_count, STBI_rgb_alpha);

  return new TextureData(image_data, width, height);
}

void Loader::unbind_vao() { glBindVertexArray(0); }

void Loader::cleanup() {
  for (unsigned int vao_id : vao_list)
    glDeleteVertexArrays(1, &vao_id);

  for (unsigned int vbo_id : vbo_list)
    glDeleteBuffers(1, &vbo_id);

  for (unsigned int texture_id : textures)
    glDeleteTextures(1, &texture_id);
}
