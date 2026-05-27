#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace LOGL {
struct Mesh {
  unsigned int VBO;
  unsigned int VAO;
  unsigned int EBO;
  unsigned int indexCount;

  Mesh(size_t size_vert, float vertices[], size_t size_indi,
       unsigned int indices[]);
  // It probably should have a destructor
};
} // namespace LOGL
