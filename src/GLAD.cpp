#include <stdexcept>
#include <LearnOpenGL/GLAD.h>

namespace LOGL::GLAD {
void InitGlad() {
  int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    throw std::runtime_error("Failed to initialize OpenGL context\n");
  }
  printf("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version),
         GLAD_VERSION_MINOR(version));
}
} // namespace LOGL::GLAD
