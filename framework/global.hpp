#ifndef __GLOBAL__HPP
#define __GLOBAL__HPP

#include <stdlib.h>

void * operator new(size_t size);
void * operator new(size_t size,void *ptr);

void operator delete(void * ptr);


__extension__ typedef int __guard __attribute__((mode (__DI__)));
extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *);
extern "C" void __cxa_pure_virtual(void);

#endif