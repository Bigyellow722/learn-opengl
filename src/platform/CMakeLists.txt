
add_subdirectory(glfwWindow)
add_library(platform OBJECT
		     $<TARGET_OBJECTS:glfwWindow>)
