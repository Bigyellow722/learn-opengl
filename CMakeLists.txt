cmake_minimum_required(VERSION 3.10)
project(OpenGL_GLFW_GLAD)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(include)
link_directories(/usr/local/lib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

add_executable(OpenGL_GLFW_GLAD src/main.c src/glad.c)

find_package(OpenGL REQUIRED)
target_link_libraries(OpenGL_GLFW_GLAD ${OPENGL_LIBRARIES} glfw)
