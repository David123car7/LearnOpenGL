#include <cstddef>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "LearnOpenGL/GLAD.h"
#include "LearnOpenGL/GLFW.h"
#include "LearnOpenGL/Shaders.h"
#include <iostream>

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = LOGL::GLFW::CreateWindow(800, 800, "LearnOpenGL");
  LOGL::GLAD::InitGlad();

  unsigned int vertexShader = LOGL::Shaders::SetupVertexShader();
  unsigned int fragmentShader = LOGL::Shaders::SetupFragmentShader();
  unsigned int shaderProgram =
      LOGL::Shaders::SetupShaderProgram(vertexShader, fragmentShader);

  // Setup rectangle vertices
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

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // Starts VAO Setep
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
               0); // this must be after unbinding the VAO
  // Ends VAO Setup

  while (!glfwWindowShouldClose(window)) {
    LOGL::GLFW::HandleInput(window);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Delete Shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glfwTerminate();
  return 0;
}
