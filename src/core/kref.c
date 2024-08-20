#include <stdio.h>
#include "kref.h"
_Atomic int global_a = 41;

void kref_set(struct kref *kref, int value)
{
    atomic_store(&kref->refcount, value);
}

void kref_inc(struct kref *kref)
{
    int old = atomic_fetch_add(&kref->refcount, 1);
}

int kref_get(struct kref *kref)
{
    int value = atomic_load(&kref->refcount);
    return value;
}

static int kref_dec_and_test(atomic_int *count)
{
    int old = atomic_fetch_sub(count, 1);
    if (old == 1)
	return 1;
    else
	return 0;
}

int kref_dec(struct kref *kref, void (*release)(struct kref *kref))
{
    if (kref_dec_and_test(&kref->refcount)) {
	release(kref);
	return 1;
    }
    return 0;
}
