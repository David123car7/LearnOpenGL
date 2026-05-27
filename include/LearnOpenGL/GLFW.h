#pragma once

#include <GLFW/glfw3.h>

namespace LOGL::GLFW {
GLFWwindow *CreateWindow(int width, int height, const char name[]);
void HandleInput(GLFWwindow *window);

// whenever the window size changed (by OS or user resize) this callback
// function executes
void Framebuffer_size_callback(GLFWwindow *window, int width, int height);
} // namespace LOGL::GLFW
