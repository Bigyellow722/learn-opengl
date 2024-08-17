
#include "log.h"
#include "memory.h"

#include <stdlib.h>
#include <string.h>

void *xmalloc(size_t size)
{
    void *res = NULL;

    res = malloc(size);
    if (!res) {
	die("xmalloc: no enough memory\n");
    }
    return res;
}

void *xrealloc(void* ptr, size_t size)
{
    void *res = NULL;

    if(!ptr) {
	die("xrealloc: ptr is null\n");
    }
    res = realloc(ptr, size);
    if (!res) {
	die("xrealloc: no enough memory\n");
    }
    return res;
}

void xfree(void *ptr)
{
    if (!ptr)
	return;

    free(ptr);
}

/* not use memcpy */
void *xmemmove(void *dest, const void *src, size_t n)
{
    return memmove(dest, src, n);
}

