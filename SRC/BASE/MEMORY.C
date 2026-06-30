#include "BASE/@BASE.H"

#define MEMORY_MAX_BLOCKS 512

typedef enum {
    MEMORY_TYPE_NEAR = 0,
    MEMORY_TYPE_FAR
} MemoryType;

typedef struct MemoryBlock {
    void *near_ptr;
    void far *far_ptr;
    unsigned long size;
    MemoryType type;
    const char *file;
    int line;
} MemoryBlock;

static MemoryBlock g_blocks[MEMORY_MAX_BLOCKS];

static int Memory_FindFreeSlot(void)
{
    int i;

    for (i = 0; i < MEMORY_MAX_BLOCKS; ++i) {
        if (g_blocks[i].near_ptr == NULL && g_blocks[i].far_ptr == NULL) {
            return i;
        }
    }

    return -1;
}

static int Memory_FindNearPtr(void *ptr)
{
    int i;

    for (i = 0; i < MEMORY_MAX_BLOCKS; ++i) {
        if (g_blocks[i].type == MEMORY_TYPE_NEAR &&
            g_blocks[i].near_ptr == ptr) {
            return i;
        }
    }

    return -1;
}

static int Memory_FindFarPtr(void far *ptr)
{
    int i;

    for (i = 0; i < MEMORY_MAX_BLOCKS; ++i) {
        if (g_blocks[i].type == MEMORY_TYPE_FAR &&
            g_blocks[i].far_ptr == ptr) {
            return i;
        }
    }

    return -1;
}

void * Memory_AllocDebug(size_t size, const char *file, int line)
{
    void *p;
    int slot;

    p = malloc(size);

    if (p == NULL) {
        printf("NEAR malloc failed: %lu bytes at %s:%d\n",
               (unsigned long)size, file, line);
        return NULL;
    }

    slot = Memory_FindFreeSlot();

    if (slot < 0) {
        printf("Memory tracker full at %s:%d\n", file, line);
        free(p);
        return NULL;
    }

    g_blocks[slot].near_ptr = p;
    g_blocks[slot].far_ptr = NULL;
    g_blocks[slot].size = (unsigned long)size;
    g_blocks[slot].type = MEMORY_TYPE_NEAR;
    g_blocks[slot].file = file;
    g_blocks[slot].line = line;

    return p;
}

void Memory_FreeDebug(void *ptr, const char *file, int line)
{
    int slot;

    if (ptr == NULL) {
        return;
    }

    slot = Memory_FindNearPtr(ptr);

    if (slot < 0) {
        printf("FREE unknown NEAR pointer at %s:%d\n", file, line);
        return;
    }

    g_blocks[slot].near_ptr = NULL;
    g_blocks[slot].far_ptr = NULL;
    g_blocks[slot].size = 0;
    g_blocks[slot].file = NULL;
    g_blocks[slot].line = 0;

    free(ptr);
}

void far * Memory_FarAllocDebug(unsigned long size, const char *file, int line)
{
    void far *p;
    int slot;

    p = farmalloc(size);

    if (p == NULL) {
        printf("FAR malloc failed: %lu bytes at %s:%d\n",
               size, file, line);
        return NULL;
    }

    slot = Memory_FindFreeSlot();

    if (slot < 0) {
        printf("Memory tracker full at %s:%d\n", file, line);
        farfree(p);
        return NULL;
    }

    g_blocks[slot].near_ptr = NULL;
    g_blocks[slot].far_ptr = p;
    g_blocks[slot].size = size;
    g_blocks[slot].type = MEMORY_TYPE_FAR;
    g_blocks[slot].file = file;
    g_blocks[slot].line = line;

    return p;
}

void Memory_FarFreeDebug(void far *ptr, const char *file, int line)
{
    int slot;

    if (ptr == NULL) {
        return;
    }

    slot = Memory_FindFarPtr(ptr);

    if (slot < 0) {
        printf("FARFREE unknown FAR pointer at %s:%d\n", file, line);
        return;
    }

    g_blocks[slot].near_ptr = NULL;
    g_blocks[slot].far_ptr = NULL;
    g_blocks[slot].size = 0;
    g_blocks[slot].file = NULL;
    g_blocks[slot].line = 0;

    farfree(ptr);
}

void Memory_DumpLeaks(void)
{
    int i;
    int leaks;
    unsigned long total;

    leaks = 0;
    total = 0;

    for (i = 0; i < MEMORY_MAX_BLOCKS; ++i) {
        if (g_blocks[i].near_ptr != NULL || g_blocks[i].far_ptr != NULL) {
            ++leaks;
            total += g_blocks[i].size;

            if (g_blocks[i].type == MEMORY_TYPE_NEAR) {
                printf("LEAK NEAR: ptr=%p size=%lu at %s:%d\n",
                       g_blocks[i].near_ptr,
                       g_blocks[i].size,
                       g_blocks[i].file,
                       g_blocks[i].line);
            } else {
                printf("LEAK FAR: ptr=%Fp size=%lu at %s:%d\n",
                       g_blocks[i].far_ptr,
                       g_blocks[i].size,
                       g_blocks[i].file,
                       g_blocks[i].line);
            }
        }
    }

    if (leaks == 0) {
        printf("No memory leaks found\n");
    } else {
        printf("Memory leaks found: %d blocks, %lu bytes\n", leaks, total);
    }
}