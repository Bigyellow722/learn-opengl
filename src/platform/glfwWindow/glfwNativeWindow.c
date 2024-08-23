#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>


#include "log.h"
#include "window.h"

typedef void* (* createNativeWindow_t)(struct windowClass *ops);

GLFWwindow *glfwCreateNativeWindow(struct windowClass *ops)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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

static struct windowClass glfwWindowOps = {
    .createNativeWindow = (createNativeWindow_t)glfwCreateNativeWindow,
    .closeNativeWindow = glfwCloseNativeWindow
};

__attribute__((constructor)) void doInitWindowClass(void)
{
    info("%s, begin\n", __func__);
    setWindowClass(&glfwWindowOps);
    info("%s, end\n", __func__);
}
