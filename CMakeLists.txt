cmake_minimum_required(VERSION 3.10)
project(OpenGL_GLFW_GLAD)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

add_subdirectory(src)

# Add the tests directory
enable_testing()
add_subdirectory(test)
