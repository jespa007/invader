#ifndef __MEMORY_H__
#define __MEMORY_H__

#define MALLOC(size)                Memory_AllocDebug((size), __FILE__, __LINE__)
#define FREE(ptr)                   Memory_FreeDebug((ptr), __FILE__, __LINE__)
#define NEW(S) ((S*)                Memory_AllocDebug(sizeof(S), __FILE__, __LINE__))
#define NEW_LENGTH(S,N) ((S*)       Memory_AllocDebug(sizeof(S)*(N),__FILE__,__LINE__))


#define FARMALLOC(size)             Memory_FarAllocDebug((size), __FILE__, __LINE__)
#define FARFREE(ptr)                Memory_FarFreeDebug((ptr), __FILE__, __LINE__)

#define NEWFAR(S) ((S*)             Memory_FarAllocDebug(sizeof(S), __FILE__, __LINE__))
#define NEWFAR_LENGTH(S,N) ((S*)    Memory_FarAllocDebug(sizeof(S)*(N),__FILE__,__LINE__))


void * Memory_AllocDebug(size_t size, const char *file, int line);
void   Memory_FreeDebug(void *ptr, const char *file, int line);

void far * Memory_FarAllocDebug(unsigned long size, const char *file, int line);
void       Memory_FarFreeDebug(void far *ptr, const char *file, int line);
#endif
