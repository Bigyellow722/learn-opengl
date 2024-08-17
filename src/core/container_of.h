#ifndef _CONTAINER_OF_H_
#define _CONTAINER_OF_H_

#undef offsetof
#define offsetof(type, member) __builtin_offsetof(type, member)

#define container_of(ptr, type, member) ({	\
  void *__mptr = (void *)(ptr);	\
  (type *)(__mptr - offsetof(type, member));	\
})


#endif
