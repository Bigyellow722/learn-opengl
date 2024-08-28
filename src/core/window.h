#ifndef _WINDOW_H_
#define _WINDOW_H_

struct window;
struct windowCap;
struct windowClass {
    void* (* createNativeWindow)(struct windowClass *ops, struct windowCap config);
    void (* closeNativeWindow)(struct window *win);
};

struct windowCap {
    char *name;
    int width;
    int height;
};

struct window {
    struct windowClass *ops;
    struct windowCap config;
    void *m_window;
};

void setWindowClass(struct windowClass *ops);
struct window* createWindow(char *name, int width, int height);
void closeWindow(struct window* win);

#endif
