#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>


#include "log.h"
#include "window.h"

int g_isGlfwInit = 0;

void *glfwCreateNativeWindow(struct windowClass *ops, struct windowCap config)
{
    if (!g_isGlfwInit) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
	g_isGlfwInit = 1;
    }
    GLFWwindow* window = glfwCreateWindow(config.width, config.height, config.name, NULL, NULL);
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

void glfwUpdateNativeWindow(struct window *win)
{
    if (!win)
	return;

    glfwSwapBuffers(win->m_window);
    glfwPollEvents();
}

static struct windowClass glfwWindowOps = {
    .createNativeWindow = glfwCreateNativeWindow,
    .closeNativeWindow = glfwCloseNativeWindow,
    .updateNativeWindow = glfwUpdateNativeWindow
};

__attribute__((constructor)) void doInitWindowClass(void)
{
    setWindowClass(&glfwWindowOps);
}
