cmake_minimum_required(VERSION 3.10)
project(OpenGL_GLFW_GLAD)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_MESSAGE_LOG_LEVEL "DEBUG")


set(OpenGL_GL_PREFERENCE "GLVND")
set(src_dir ${CMAKE_CURRENT_SOURCE_DIR})

# find opengl
link_directories(/usr/local/lib)
find_package(OpenGL REQUIRED)


add_subdirectory(src)
add_subdirectory(vendor)


add_library(template STATIC $<TARGET_OBJECTS:core> $<TARGET_OBJECTS:platform>)
target_include_directories(template PUBLIC
				    ${CMAKE_CURRENT_SOURCE_DIR}/include
				    ${CMAKE_CURRENT_SOURCE_DIR}/src/
				    )
target_link_libraries(template PUBLIC ${OPENGL_LIBRARIES} glad glfw platform core cglm m)

# Add the tests directory
enable_testing()
add_subdirectory(test)
