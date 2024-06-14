
#include <stdlib.h>
#include "../../global.hpp"

void * operator new(size_t size)
{
	return malloc(size);
}
void operator delete(void * ptr,size_t size)
{
	free(ptr);
}
void * operator new(size_t size,void *ptr){
	return ptr;
}

