#include "memoryVM.h"


/**
 * @brief allocate
 * @param size
 * @return
 */
void *allocate(size_t size)
{
    void(**dtor__counter__memory)(void *) = malloc(size + sizeof(size_t) + sizeof(void *));
    if (dtor__counter__memory == NULL) {
        perror("dtor__counter__memory");
        return NULL;
    }
    *dtor__counter__memory = NULL;
    size_t *counter__memory = (size_t *)(dtor__counter__memory + 1);
    memset(counter__memory, 0, size + sizeof(size_t));
    *counter__memory = 1;
    return (void *)(counter__memory + 1);
}

/**
 * @brief allocateArray
 * @param elementSize
 * @param elementCount
 * @return
 */
void *allocateArray(size_t elementSize, size_t elementCount)
{
    return allocate(elementSize * elementCount);
}

/**
 * @brief allocateOuterArray allocates array of pointers to arrays for 2D array
 * @param subarrays number of arrays pointed to by pointers of array being allocated
 * @return the allocated array
 */
void **allocateOuterArray(size_t subarrays)
{
    size_t range = subarrays * sizeof(void *) + 2 * sizeof(size_t);
    size_t *length__counter__array = malloc(range);
    if (length__counter__array == NULL) {
        perror("length__counter__array");
        return NULL;
    }
    memset(length__counter__array, 0, range);
    *length__counter__array = subarrays;
    size_t *counter__array = length__counter__array + 1;
    *counter__array = 1;
    return (void **)(counter__array + 1);
}

/**
 * @brief allocateArray2D
 * @param elementSize
 * @param subarrays
 * @param elementCounts
 * @return
 */
void **allocateArray2D(size_t elementSize, size_t subarrays, size_t *elementCounts)
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

/**
 * @brief acquire
 * @param memory
 */
void *acquire(void *memory)
{
    if (memory == NULL) {
        return NULL;
    }
    size_t *counter__memory = (size_t *)memory - 1;
    if (counter__memory == 0) {
        return NULL;
    }
    *counter__memory += 1;
    return memory;
}

/**
 * @brief acquireArray2D
 * @param array
 */
void **acquireArray2D(void **array)
{
    if (array == NULL) {
        return NULL;
    }
    size_t *counter_array = (size_t *)array - 1;
    if (*counter_array == 0) {
        return NULL;
    }
    acquire(array);
    size_t subarrays = *((size_t *)array - 2);
    for (size_t i = 0; i < subarrays; i++) {
        acquire(array[i]);
    }
    return array;
}

/**
 * @brief release
 * @param memory
 * @return
 */
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

/**
 * @brief releaseArray2D
 * @param array
 * @return
 */
int releaseArray2D(void **array)
{
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
