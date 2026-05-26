# LearnOpenGL
This repository contains all my code as I follow along with the [LearnOpenGL book](https://learnopengl.com/book/book_pdf.pdf).

# How to run

### Install packages

```bash
conan install . --output-folder=build --build=missing
```

### Build

```bash
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=build/build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Run 

```bash
./build/learn-opengl
```

# Librarys

- [GLFW](https://github.com/glfw/glfw) 
