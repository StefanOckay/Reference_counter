#include "memoryVM.h"


void *allocate(size_t size)
{
    void(**dtor__counter__memory)(void *) = malloc(size + sizeof(size_t) + sizeof(void *));
    if (dtor__counter__memory == NULL) {
        perror("allocate");
        return NULL;
    }
    *dtor__counter__memory = NULL;
    size_t *counter__memory = (size_t *)(dtor__counter__memory + 1);
    memset(counter__memory, 0, size + sizeof(size_t));
    *counter__memory = 1;
    return (void *)(counter__memory + 1);
}

void *allocateArray(size_t elementSize, size_t elementCount)
{
    return allocate(elementSize * elementCount);
}

void **allocateOuterArray(size_t subarrays)
{
    size_t range = subarrays * sizeof(void *) + 2 * sizeof(size_t);
    size_t *length__counter__array = malloc(range);
    if (length__counter__array == NULL) {
        perror("allocateOuterArray");
        return NULL;
    }
    memset(length__counter__array, 0, range);
    *length__counter__array = subarrays;
    size_t *counter__array = length__counter__array + 1;
    *counter__array = 1;
    return (void **)(counter__array + 1);
}

void *allocateArray2D(size_t elementSize, size_t subarrays, size_t *elementCounts)
{
    void **array2D = allocateOuterArray(subarrays);
    if (array2D == NULL) {
        return NULL;
    }
    size_t row_elements = subarrays;
    for (size_t i = 0; i < subarrays; i++) {
        if (elementCounts != NULL) {
            row_elements = elementCounts[i];
        }
        array2D[i] = allocateArray(elementSize, row_elements);
        if (array2D[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free((size_t *)array2D[j] - 1);
            }
            free((size_t *)array2D - 1);
            return NULL;
        }
    }
    return array2D;
}

void *allocateNew(size_t size, int(*ctor)(void *, void **), void(*dtor)(void *), void **params)
{
    if (size == 0) {
        fprintf(stderr, "Invalid block size: %zu\n", size);
        return NULL;
    }
    size_t range = sizeof(void (*)(void *)) + sizeof(size_t) + size;
    void (**dtor__counter__memory)(void *) = malloc(range);
    if (dtor__counter__memory == NULL) {
        perror("allocateNew");
        return NULL;
    }
    *dtor__counter__memory = dtor;
    size_t *counter__memory = (size_t *)(dtor__counter__memory + 1);
    void *memory = (void *)(counter__memory + 1);
    if (ctor(memory, params)) {
        free(dtor__counter__memory);
        return NULL;
    }
    *counter__memory = 1;
    return memory;
}

void *acquire(void *memory)
{
    if (memory == NULL) {
        return NULL;
    }
    size_t *counter__memory = (size_t *)memory - 1;
    *counter__memory += 1;
    return memory;
}

void *acquireArray2D(void *array2D)
{
    void **array = array2D;
    if (array == NULL) {
        return NULL;
    }
    acquire(array);
    size_t subarrays = *((size_t *)array - 2);
    for (size_t i = 0; i < subarrays; i++) {
        acquire(array[i]);
    }
    return array;
}

int release(void *memory)
{
    if (memory == NULL) {
        return 1;
    }
    size_t *counter__memory = (size_t *)memory - 1;
    void(**dtor__counter__memory)(void *) = (void(**)(void *))counter__memory - 1;
    if (*counter__memory == 1) {
        if (*dtor__counter__memory != NULL) {
            (*dtor__counter__memory)(memory);
        }
        free(dtor__counter__memory);
        return 0;
    }
    *counter__memory -= 1;
    return 1;
}

int releaseArray2D(void *array2D)
{
    void **array = array2D;
    if (array == NULL) {
        return 1;
    }
    size_t length__counter__array = *((size_t *)array - 2);
    for (size_t i = 0; i < length__counter__array; i++) {
        release(array[i]);
    }
    size_t *counter__array = (size_t *)array - 1;
    if (*counter__array == 1) {
        size_t *length__counter__array = counter__array - 1;
        free(length__counter__array);
        return 0;
    }
    *counter__array -= 1;
    return 1;
}
