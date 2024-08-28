#include "window.h"
#include "memory.h"
#include "log.h"
#include <stdlib.h>
#include <string.h>
struct windowClass* g_window_ops = NULL;

void setWindowClass(struct windowClass *ops)
{
    g_window_ops = ops;
}


struct window* __createWindow(struct windowClass *ops, char *name, int width, int height)
{
    struct window *win = NULL;
    size_t name_len = 0;

    if (!ops) {
	err("%s, no ops of native window\n", __func__);
	goto err_no_ops;
    }
    win = xmalloc(sizeof(struct window));
    if (!win) {
	goto err_alloc_win;
    }
    name_len = strlen(name);
    win->config.name = malloc(sizeof(char) * (name_len + 1));
    memcpy(win->config.name, name, name_len);
    win->config.name[name_len] = '\0';
    win->config.width = width;
    win->config.height = height;
    win->ops = ops;
    if (win->ops->createNativeWindow) {
	win->m_window = win->ops->createNativeWindow(ops, win->config);
	if (!win->m_window) {
	    err("%s: failed tp create native window", __func__);
	    goto err_create_native_window;
	}
    } else {
	err("%s: no native function for native window\n", __func__);
	goto err_create_native_window;
    }
    return win;
err_create_native_window:
    xfree(win);
err_alloc_win:
err_no_ops:
    return NULL;
}


struct window* createWindow(char *name, int width, int height)
{
    return __createWindow(g_window_ops, name, width, height);
}

void closeWindow(struct window* win)
{
    if (!win)
	return;
    else if (!win->ops) {
	err("%s, no ops of native window\n", __func__);
	goto err_no_ops;
    } else {
	win->ops->closeNativeWindow(win);
    }
err_no_ops:
    xfree(win);
    win = NULL;
}
