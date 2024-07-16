include_directories(../include)
link_directories(/usr/local/lib)
find_package(OpenGL REQUIRED)

add_library(template glad.c)
target_link_libraries(template ${OPENGL_LIBRARIES} glfw)

add_executable(main main.c)
target_link_libraries(main ${OPENGL_LIBRARIES} glfw template)


