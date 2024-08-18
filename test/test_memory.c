#include "memory.h"
#include "log.h"

#include <string.h>

int main(void)
{
    char *source = "template: test memory utils\n";
    size_t source_len = strlen(source);
    char *dst = xmalloc(sizeof(char) * source_len + 1);
    info("source: %s", source);
    xmemmove(dst, source, source_len + 1);
    info("dst: %s", dst);
}
