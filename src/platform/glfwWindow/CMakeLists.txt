# find opengl
link_directories(/usr/local/lib)
find_package(OpenGL REQUIRED)


add_library(glfwWindow OBJECT
		       glfwNativeWindow.c)
target_include_directories(glfwWindow PUBLIC
				    ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(glfwWindow PUBLIC
				 core
				 glad
				 glfw
				 ${OPENGL_LIBRARIES})

