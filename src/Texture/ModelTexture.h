#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

class ModelTexture {
public:
  ModelTexture(unsigned int textureID) : textureID(textureID) {}

  unsigned int getID() const { return this->textureID; }
  int getNumberOfRows() const { return this->numberOfRows; }
  float getShineDamper() const { return this->shineDamper; }
  float getReflectivity() const { return this->reflectivity; }
  bool hasTransparency() const { return this->transparency; }
  bool usesFakeLighting() const { return this->fakeLighting; }

  void setNumberOfRows(int value) { this->numberOfRows = value; }
  void setReflectivity(float value) { this->reflectivity = value; }
  void setShineDamper(float value) { this->shineDamper = value; }
  void setTransparency(bool value) { this->transparency = value; }
  void useFakeLighting(bool value) { this->fakeLighting = value; }

private:
  unsigned int textureID;
  int numberOfRows = 1;
  float shineDamper = 1;
  float reflectivity = 0;
  bool transparency = false;
  bool fakeLighting = false;
};

#endif // !MODELTEXTURE_H
