#include <cstddef>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "LearnOpenGL/GLAD.h"
#include "LearnOpenGL/GLFW.h"
#include <iostream>

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = LOGL::GLFW::CreateWindow(800, 800, "LearnOpenGL");
  LOGL::GLAD::InitGlad();

  // Vertex Shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  int vertexShaderSucess;
  char vertexInfoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderSucess);
  if (!vertexShaderSucess) {
    glGetShaderInfoLog(vertexShader, 512, NULL, vertexInfoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << vertexInfoLog << std::endl;
  }

  // FragmentShader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  int fragmentShaderSucess;
  char fragmentInfoLog[512];
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderSucess);
  if (!fragmentShaderSucess) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, fragmentInfoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << fragmentInfoLog << std::endl;
  }

  // Link shaders
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  int shaderProgramSucess;
  char shaderProgramInfoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderProgramSucess);
  if (!shaderProgramSucess) {
    glGetProgramInfoLog(shaderProgram, sizeof(shaderProgramInfoLog), NULL,
                        shaderProgramInfoLog);
    std::cout << "ERROR::SHADERPROGRAM::LINK_FAILED\n"
              << shaderProgramInfoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Setup triangle vertices
  // float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f,
  // 0.0f};

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
