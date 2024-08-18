#ifndef _WINDOW_H_
#define _WINDOW_H_

struct window;

struct windowNativeOps {
    void* (* createNativeWindow)(struct windowNativeOps *ops);
    void (* closeNativeWindow)(struct window *win);
};

struct window {
    struct windowNativeOps *ops;
    void *m_window;
};


struct window* createWindow(struct windowNativeOps *ops);
void closeWindow(struct window* win);

#endif
