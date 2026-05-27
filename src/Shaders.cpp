#include "LearnOpenGL/Shaders.h"
#include <iostream>
#include <stdexcept>

namespace LOGL::Shaders {

unsigned int SetupShaderProgram(unsigned int vertexShader,
                                unsigned int fragmentShader) {
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  int sucess;
  char log[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess);
  if (!sucess) {
    glGetProgramInfoLog(shaderProgram, sizeof(log), NULL, log);
    throw std::runtime_error(std::string("ERROR::SHADERPROGRAM::LINK_FAILED") +
                             log);
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  return shaderProgram;
}

unsigned int SetupVertexShader() {
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
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

unsigned int SetupFragmentShader() {
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
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
} // namespace LOGL::Shaders
