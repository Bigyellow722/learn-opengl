#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    /* the first two parameters set the location of the lower left corner of the window */
    /* the third and fourth parameter set the width and height of the rendering window in pixels */
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 400, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    /* GLFW will call frambuffer_size_callback on every window resize */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* load the address of the opengl function pointers which is OS-specific */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    /* render loop */
    while (!glfwWindowShouldClose(window)) {
	/* input handler defined by user */
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	/* whenever glClear is called, the entire color buffer will be filled with the color as configured by glClearColor. */
        glClear(GL_COLOR_BUFFER_BIT);

	/* swap buffer */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
