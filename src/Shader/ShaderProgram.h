#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

class ShaderProgram {
public:
  ShaderProgram(std::string vertexFilePath, std::string fragmentFilePath);

  void start();
  void stop();
  void cleanup();
  static int loadShader(std::string source, int type);

  int getUniformLocation(std::string uniformName);

protected:
  virtual void bindAttributes() = 0;
  virtual void getAllUniformLocations() = 0;
  void bindAttribute(int attribute, std::string variableName);

  void loadInt(int location, int value);
  void loadFloat(int location, float value);
  void loadVector(int location, glm::vec3 vector);
  void loadVector2D(int location, glm::vec2 vector);
  void loadBool(int location, bool value);
  void loadMatrix(int location, glm::mat4 matrix);

private:
  unsigned int programID;
  unsigned int vertexShaderID;
  unsigned int fragmentShaderID;

  static bool hasErrors(unsigned int shaderID, int type);
};

#endif // !SHADERPROGRAM_H
