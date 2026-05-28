#include "LearnOpenGL/Shader.h"
#include "LearnOpenGL/Helpers/IO.h"
#include <glad/gl.h>
#include <stdexcept>

namespace LOGL {
Shader::Shader(const char *vertexPath, const char *fragmentPath) {
  std::string vShaderCode = LOGL::Helpers::IO::readFile(vertexPath);
  std::string fshaderCode = LOGL::Helpers::IO::readFile(fragmentPath);
  unsigned int vShader = setupVertexShader(vShaderCode.c_str());
  unsigned int fShader = setupFragmentShader(fshaderCode.c_str());
  this->ID = glCreateProgram();
  glAttachShader(this->ID, vShader);
  glAttachShader(this->ID, fShader);
  glLinkProgram(this->ID);
  int sucess;
  char log[512];
  glGetProgramiv(this->ID, GL_LINK_STATUS, &sucess);
  if (!sucess) {
    glGetProgramInfoLog(this->ID, sizeof(log), NULL, log);
    throw std::runtime_error(std::string("ERROR::SHADERPROGRAM::LINK_FAILED") +
                             log);
  }
  glDeleteShader(vShader);
  glDeleteShader(fShader);
}

unsigned int Shader::setupVertexShader(const char *src) {
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &src, NULL);
  glCompileShader(vertexShader);
  int sucess;
  char log[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);
  if (!sucess) {
    glGetShaderInfoLog(vertexShader, 512, NULL, log);
    throw std::runtime_error(
        std::string("ERROR::SHADER::VERTEX::COMPILATION_FAILED") + log);
  }
  return vertexShader;
}

unsigned int Shader::setupFragmentShader(const char *src) {
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &src, NULL);
  glCompileShader(fragmentShader);
  int sucess;
  char log[512];
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &sucess);
  if (!sucess) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, log);
    throw std::runtime_error(
        std::string("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED") + log);
  }
  return fragmentShader;
}
} // namespace LOGL
