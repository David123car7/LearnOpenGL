#include <GLFW/glfw3.h>
#include "LearnOpenGL/GLFW.h"
#include <stdexcept>
namespace LOGL::GLFW {
GLFWwindow *CreateWindow(int width, int height, const char name[]) {
  GLFWwindow *window = glfwCreateWindow(width, height, name, NULL, NULL);
  if (window == NULL) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW Window");
  }
  glfwMakeContextCurrent(window); // should this be here?
  glfwSetFramebufferSizeCallback(window, Framebuffer_size_callback);
  return window;
}

void HandleInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void Framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
} // namespace LOGL::GLFW
