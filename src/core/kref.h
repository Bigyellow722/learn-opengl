#ifndef _KREF_H_
#define _KREF_H_
#include <stdatomic.h>

struct kref {
    atomic_int refcount;
};

void kref_set(struct kref *kref, int value);
int kref_get(struct kref *kref);
void kref_inc(struct kref *kref);
int kref_dec(struct kref *kref, void (*release)(struct kref *kref));

#endif
