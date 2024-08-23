#ifndef _WINDOW_H_
#define _WINDOW_H_

struct window;

struct windowClass {
    void* (* createNativeWindow)(struct windowClass *ops);
    void (* closeNativeWindow)(struct window *win);
};

struct window {
    struct windowClass *ops;
    void *m_window;
};

void setWindowClass(struct windowClass *ops);
struct window* createWindow(void);
void closeWindow(struct window* win);

#endif
