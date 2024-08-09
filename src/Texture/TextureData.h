#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

#include "stb_image.h"

class TextureData {
public:
  TextureData(stbi_uc* image_data, int width, int height)
      : width(width), height(height), buffer(image_data) {}

  int get_width() const { return this->width; }
  int get_height() const { return this->height; }
  stbi_uc* get_buffer() const { return this->buffer; }

private:
  int width;
  int height;
  stbi_uc* buffer;
};

#endif // !TEXTUREDATA_H
