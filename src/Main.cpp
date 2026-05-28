#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "LearnOpenGL/GLAD.h"
#include "LearnOpenGL/GLFW.h"
#include "LearnOpenGL/Shader.h"
#include "LearnOpenGL/Mesh.h"

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = LOGL::GLFW::CreateWindow(800, 800, "LearnOpenGL");
  LOGL::GLAD::InitGlad();

  LOGL::Shader shader{"res/shaders/VertexShader.glsl",
                      "res/shaders/FragmentShader.glsl"};

  float vertices[] = {
      0.5f,  0.5f,  0.0f, // top right
      0.5f,  -0.5f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f  // top left
  };
  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  LOGL::Mesh cube{sizeof(vertices), vertices, sizeof(indices), indices};

  while (!glfwWindowShouldClose(window)) {
    LOGL::GLFW::HandleInput(window);
    shader.use();
    glBindVertexArray(cube.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
