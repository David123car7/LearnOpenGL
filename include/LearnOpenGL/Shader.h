#pragma once

#include <glad/gl.h>
#include <string>

namespace LOGL {
class Shader {
public:
  unsigned int ID;

  Shader(const char *vertexPath, const char *fragmentPath);
  void use() { glUseProgram(this->ID); }
  void setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
  }
  void setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
  }
  void setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
  }

private:
  unsigned int setupVertexShader(const char *src);
  unsigned int setupFragmentShader(const char *src);
};
} // namespace LOGL
