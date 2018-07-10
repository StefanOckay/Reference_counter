#include "memoryVM.h"


/**
 * @brief allocate
 * @param size
 * @return
 */
void *allocate(size_t size) {
    if (size <= 0) {
        fprintf(stderr, "Invalid block size: %zu\n", size);
        return NULL;
    }
    size_t *counter__array = malloc(size + sizeof(size_t));
    if (counter__array == NULL) {
        perror("Memory allocation failure.");
        return NULL;
    }
    memset(counter__array, 0, size + sizeof(size_t));
    *counter__array = 1;
    return (void *)(counter__array + 1);
}

/**
 * @brief allocateArray
 * @param elementSize
 * @param elementCount
 * @return
 */
void *allocateArray(size_t elementSize, size_t elementCount) {
    return allocate(elementCount * elementSize);
}

/**
 * @brief allocateOuterArray allocates array of pointers to arrays for 2D array
 * @param subarrays number of arrays pointed to by pointers of array being allocated
 * @return the allocated array
 */
void *allocateOuterArray(size_t subarrays) {
    if (subarrays <= 0) {
        fprintf(stderr, "Invalid number of subarrays: %zu\n", subarrays);
        return NULL;
    }
    size_t range = subarrays * sizeof(void *) + 2 * sizeof(size_t);
    size_t *length__counter__array = malloc(range);
    if (length__counter__array == NULL) {
        perror("Memory allocation failure.");
        return NULL;
    }
    memset(length__counter__array, 0, range);
    *length__counter__array = subarrays;
    length__counter__array += 1;
    *length__counter__array = 1;
    return (void *)(length__counter__array + 1);
}

/**
 * @brief allocateArray2D
 * @param elementSize
 * @param subarrays
 * @param elementCounts
 * @return
 */
void **allocateArray2D(size_t elementSize, size_t subarrays, size_t *elementCounts) {
    void **arrays = allocateOuterArray(subarrays);
    if (arrays == NULL) {
        return NULL;
    }
    size_t row_elements;
    for (size_t i = 0; i < subarrays; i++) {
        if (elementCounts == NULL) {
            row_elements = subarrays;
        } else {
            row_elements = elementCounts[i];
        }
        arrays[i] = allocateArray(elementSize, row_elements);
        if (arrays[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free((size_t *)arrays[j] - 1);
            }
            free((size_t *)arrays - 1);
            perror("Memory allocation failure.");
            return NULL;
        }
    }
    return arrays;
}

/**
 * @brief acquire
 * @param memory
 */
void acquire(void *memory) {
    if (memory == NULL) {
        return;
    }
    size_t *counter = (size_t *)memory - 1;
    if (counter == 0) {
        return;
    }
    *counter += 1;
}

/**
 * @brief acquireArray2D
 * @param array
 */
void acquireArray2D(void **array) {
    if (array == NULL) {
        return;
    }
    if (*((size_t *)array - 1) == 0) {
        return;
    }
    acquire(array);
    size_t subarrays = *((size_t *)array - 2);
    for (size_t i = 0; i < subarrays; i++) {
        acquire(array[i]);
    }
}

/**
 * @brief release
 * @param memory
 * @return
 */
bool release(void *memory) {
    if (memory == NULL) {
        return false;
    }
    size_t *counter = (size_t *)memory - 1;
    if (*counter == 1) {
        free(counter);
        return true;
    }
    *counter -= 1;
    return false;
}

/**
 * @brief releaseArray2D
 * @param array
 * @return
 */
bool releaseArray2D(void **array) {
    if (array == NULL) {
        return false;
    }
    size_t lena = *((size_t *)array - 2);
    for (size_t i = 0; i < lena; i++) {
        release(array[i]);
    }
    size_t *counter = (size_t *)array - 1;
    if (*counter == 1) {
        size_t *whole_memblock = counter - 1;
        free(whole_memblock);
        return true;
    }
    *counter -= 1;
    return false;
}
