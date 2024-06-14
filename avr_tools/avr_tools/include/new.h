/*
 * new.h
 *
 * Created: 07.04.2023 20:44:57
 *  Author: MainUser
 */ 


#ifndef NEW_H_
#define NEW_H_


#include <stdlib.h>

/*!
	\brief operator new
	\warning bad idea to use it
*/
[[deprecated("using malloc/free is a bad idea")]]
inline __attribute__((always_inline))  void * operator new(size_t size)
{
	return malloc(size);
}

/*!
	\brief operator delete
	\warning bad idea to use it
*/
[[deprecated("using malloc/free is bad idea")]]
inline __attribute__((always_inline))  void operator delete(void * ptr,size_t size)
{
	free(ptr);
}

/*!
	\brief placement operator new
*/
inline __attribute__((always_inline)) void * operator new(size_t size,void *ptr) {
	return ptr;
}


#endif /* NEW_H_ */