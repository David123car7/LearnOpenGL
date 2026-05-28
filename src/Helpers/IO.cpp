#include "LearnOpenGL/Helpers/IO.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace LOGL::Helpers::IO {
std::string readFile(const char *filePath) {
  std::string fileContent;
  std::ifstream file;
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    file.open(filePath);
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << file.rdbuf();
    file.close();
    fileContent = vShaderStream.str();
  } catch (std::ifstream::failure &e) {
    throw std::ifstream::failure(std::string("ERROR::READING_FILE::") +
                                 filePath + e.what());
  }
  return fileContent;
}
} // namespace LOGL::Helpers::IO
