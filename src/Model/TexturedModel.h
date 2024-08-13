#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H

#include "RawModel.h"
#include "Texture/ModelTexture.h"
#include <memory>

class TexturedModel {
public:
  TexturedModel(
    std::unique_ptr<RawModel> model,
    std::unique_ptr<ModelTexture> texture
  ) {
    this->raw_model = std::move(model);
    this->texture = std::move(texture);
  }

  RawModel* get_raw_model() const { return this->raw_model.get(); }
  ModelTexture* get_texture() const { return this->texture.get(); }

private:
  std::unique_ptr<RawModel> raw_model;
  std::unique_ptr<ModelTexture> texture;
};

#endif // !TEXTUREDMODEL_H
