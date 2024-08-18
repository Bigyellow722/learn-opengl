#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include "log.h"
#include "window.h"

typedef void* (* createNativeWindow_t)(struct windowNativeOps *ops);

GLFWwindow *glfwCreateNativeWindow(struct windowNativeOps *ops)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    GLFWwindow* window = glfwCreateWindow(800, 400, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        err("Failed to create GLFW window\n");
        glfwTerminate();
        return NULL;
    }
    return window;
}

void glfwCloseNativeWindow(struct window *win)
{
    if (!win)
	return;

    glfwTerminate();
}

static struct windowNativeOps glfwWindowOps = {
    .createNativeWindow = (createNativeWindow_t)glfwCreateNativeWindow,
    .closeNativeWindow = glfwCloseNativeWindow
};
