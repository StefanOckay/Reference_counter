#include "memoryVMObject.h"


void *allocateNew(size_t size, int(*ctor)(void *, void **), void(*dtor)(void *), void **params)
{
    if (size == 0) {
        fprintf(stderr, "Invalid block size: %zu\n", size);
        return NULL;
    }
    size_t range = sizeof(void (*)(void *)) + sizeof(size_t) + size;
    void (**dtor__counter__memory)(void *) = malloc(range);
    if (dtor__counter__memory == NULL) {
        perror("dtor__counter__memory");
        return NULL;
    }
    *dtor__counter__memory = dtor;
    size_t *counter__memory = (size_t *)(dtor__counter__memory + 1);
    void *memory = (void *)(counter__memory + 1);
    if (!ctor(memory, params)) {
        free(dtor__counter__memory);
        return NULL;
    }
    *counter__memory = 1;
    return memory;
}
