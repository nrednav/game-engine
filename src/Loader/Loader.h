#ifndef LOADER_H
#define LOADER_H

#include "Model/RawModel.h"
#include "Texture/TextureData.h"

#include <vector>
#include <string>

class Loader {
public:
  Loader();
  ~Loader();

  RawModel* load_to_vao(
    std::vector<float>& positions,
    std::vector<int>& indices,
    std::vector<float>& texture_coords,
    std::vector<float>& normals
  );
  RawModel* load_to_vao(std::vector<float>& positions, int dimensions);
  int load_texture(std::string fileName, bool repeat = false);
  int load_cube_map(std::vector<std::string>& texture_files);

private:
  std::vector<unsigned int> vao_list;
  std::vector<unsigned int> vbo_list;
  std::vector<unsigned int> textures;

  unsigned int create_vao();
  void unbind_vao();
  void store_data_in_attribute_list(
    int attribute_id,
    int component_count,
    std::vector<float>& data
  );
  void bind_indices_buffer(std::vector<int>& indices);
  TextureData* decode_texture_file(std::string filename);
};

#endif // !LOADER_H
