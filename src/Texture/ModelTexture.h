#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

class ModelTexture {
public:
  ModelTexture(unsigned int texture_id) : texture_id(texture_id) {}

  unsigned int get_id() const { return this->texture_id; }
  int get_row_count() const { return this->row_count; }
  float get_shine_damper() const { return this->shine_damper; }
  float get_reflectivity() const { return this->reflectivity; }
  bool has_transparency() const { return this->transparency; }
  bool uses_fake_lighting() const { return this->fake_lighting; }

  void set_row_count(int value) { this->row_count = value; }
  void set_reflectivity(float value) { this->reflectivity = value; }
  void set_shine_damper(float value) { this->shine_damper = value; }
  void set_transparency(bool value) { this->transparency = value; }
  void use_fake_lighting(bool value) { this->fake_lighting = value; }

private:
  unsigned int texture_id;
  int row_count = 1;
  float shine_damper = 1;
  float reflectivity = 0;
  bool transparency = false;
  bool fake_lighting = false;
};

#endif // !MODELTEXTURE_H
