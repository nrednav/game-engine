#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H

#include "RawModel.h"
#include "Texture/ModelTexture.h"

class TexturedModel {
public:
  TexturedModel(RawModel* model, ModelTexture* texture)
      : raw_model(model), texture(texture) {}

  RawModel* get_raw_model() const { return this->raw_model; }
  ModelTexture* get_texture() const { return this->texture; }

private:
  RawModel* raw_model;
  ModelTexture* texture;
};

#endif // !TEXTUREDMODEL_H
