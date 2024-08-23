#include "window.h"
#include "memory.h"
#include "log.h"
#include <stdlib.h>

struct windowClass* g_window_ops = NULL;

void setWindowClass(struct windowClass *ops)
{
    g_window_ops = ops;
}


struct window* __createWindow(struct windowClass *ops)
{
    struct window *win = NULL;

    if (!ops) {
	err("%s, no ops of native window\n", __func__);
	goto err_no_ops;
    }
    win = xmalloc(sizeof(struct window));
    if (!win) {
	goto err_alloc_win;
    }
    
    win->ops = ops;
    if (win->ops->createNativeWindow) {
	win->m_window = win->ops->createNativeWindow(ops);
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


struct window* createWindow(void)
{
    return __createWindow(g_window_ops);
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
