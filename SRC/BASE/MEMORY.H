#ifndef __MEMORY_H__
#define __MEMORY_H__


#define MALLOC(memory_bytes) (my_malloc(memory_bytes))
#define NEW(S) ((S*)my_malloc(sizeof(S)))
#define NEW_LENGTH(S,N) ((S*)my_malloc(sizeof(S)*(N)))
#define FREE(_ptr) my_free(_ptr)

void * my_malloc(size_t _size);
void   my_free(void * _ptr);

#endif
