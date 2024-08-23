#include "core/log.h"

int main()
{
    err("%s, hello\n", __func__);
    warn("%s, hello\n", __func__);
    note("%s, hello\n", __func__);
    info("%s, hello\n", __func__);
    dbg("%s, hello\n", __func__);
}
