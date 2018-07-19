#ifndef MEMORYVM_H
#define MEMORYVM_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/**
 * @brief allocate
 * @param size
 * @return
 */
void *allocate(size_t size);

/**
 * @brief allocateArray
 * @param elementSize
 * @param elementCount
 * @return
 */
void *allocateArray(size_t elementSize, size_t elementCount);

/**
 * @brief allocateOuterArray
 * @param subarrays
 * @return
 */
void **allocateOuterArray(size_t subarrays);

/**
 * @brief allocateArray2D
 * @param elementSize
 * @param subarrays
 * @param elementCounts
 * @return
 */
void **allocateArray2D(size_t elementSize, size_t subarrays, size_t *elementCounts);

/**
 * @brief acquire
 * @param memory
 */
void *acquire(void *memory);

/**
 * @brief acquireArray2D
 * @param array
 */
void **acquireArray2D(void **array);

/**
 * @brief release
 * @param memory
 * @return
 */
int release(void *memory);

/**
 * @brief releaseArray2D
 * @param array
 * @return
 */
int releaseArray2D(void **array);

#endif /* MEMORYVM_H */
