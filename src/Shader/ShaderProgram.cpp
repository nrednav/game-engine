#include "GL/glew.h"
#include "ShaderProgram.h"

#include <fstream>
#include <iostream>

ShaderProgram::ShaderProgram(std::string vertexFilePath,
                             std::string fragmentFilePath) {
  this->vertexShaderID = loadShader(vertexFilePath, GL_VERTEX_SHADER);
  this->fragmentShaderID = loadShader(fragmentFilePath, GL_FRAGMENT_SHADER);
  this->programID = glCreateProgram();
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  glLinkProgram(programID);
  glValidateProgram(programID);
}

void ShaderProgram::start() { glUseProgram(this->programID); }

void ShaderProgram::stop() { glUseProgram(0); }

void ShaderProgram::cleanup() {
  stop();
  glDetachShader(this->programID, this->vertexShaderID);
  glDetachShader(this->programID, this->fragmentShaderID);
  glDeleteShader(this->vertexShaderID);
  glDeleteShader(this->fragmentShaderID);
  glDeleteProgram(this->programID);
}

int ShaderProgram::loadShader(std::string source, int type) {
  std::string shaderSource, line;
  std::ifstream shaderFile(source);

  while (std::getline(shaderFile, line)) {
    shaderSource += line + "\n";
  }

  const GLchar* shaderCode = shaderSource.c_str();

  unsigned int shaderID = glCreateShader(type);
  glShaderSource(shaderID, 1, &shaderCode, NULL);
  glCompileShader(shaderID);

  return hasErrors(shaderID, type) ? -1 : shaderID;
}

void ShaderProgram::bindAttribute(int attribute, std::string variableName) {
  glBindAttribLocation(this->programID, attribute,
                       (const GLchar*)variableName.c_str());
}

int ShaderProgram::getUniformLocation(std::string uniformName) {
  return glGetUniformLocation(this->programID,
                              (const GLchar*)uniformName.c_str());
}

bool ShaderProgram::hasErrors(unsigned int shaderID, int type) {
  int success;
  char infoLog[512];
  std::string shaderType = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";

  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
    std::cout << "ERROR::SHADER_COMPILATION_ERROR::" << shaderType << "\n"
              << infoLog << std::endl;
    return true;
  }

  return false;
}

// Uniform methods
void ShaderProgram::loadInt(int location, int value) {
  glUniform1i(location, value);
}

void ShaderProgram::loadFloat(int location, float value) {
  glUniform1f(location, value);
}

void ShaderProgram::loadVector(int location, glm::vec3 vector) {
  glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::loadVector2D(int location, glm::vec2 vector) {
  glUniform2f(location, vector.x, vector.y);
}

void ShaderProgram::loadBool(int location, bool value) {
  glUniform1f(location, value ? 1.0f : 0.0f);
}

void ShaderProgram::loadMatrix(int location, glm::mat4 matrix) {
  glUniformMatrix4fv(location, 1, false, &matrix[0][0]);
}
