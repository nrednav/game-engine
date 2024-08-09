#ifndef TERRAINTEXTURE_H
#define TERRAINTEXTURE_H

class TerrainTexture {
public:
  TerrainTexture(unsigned int texture_id) : texture_id(texture_id) {}

  unsigned int get_texture_id() const { return this->texture_id; }

private:
  unsigned int texture_id;
};

#endif // !TERRAINTEXTURE_H
