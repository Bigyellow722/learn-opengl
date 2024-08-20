#include <stdio.h>
#include "kref.h"


static void release_test(struct kref *kref)
{
    printf("just test\n");
}

int main()
{
    struct kref ref;
    kref_set(&ref, 0);
    kref_inc(&ref);
    kref_inc(&ref);
    int value = kref_get(&ref);
    printf("%d\n", value);
    kref_dec(&ref, release_test);
    value = kref_get(&ref);
    printf("%d\n", value);
    kref_dec(&ref, release_test);
    
    return 0;
}

