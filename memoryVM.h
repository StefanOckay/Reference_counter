#ifndef MEMORYVM_H
#define MEMORYVM_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/**
 * @brief allocate .. memory to be used along with reference counter preceding the memory block
 * and pointer to destructor which is NULL in order to unify release function, also sets memory to 0
 * @param size .. bytes to allocate
 * @return part of memory that is about to be used, NULL if theres insufficient memory
 */
void *allocate(size_t size);

/**
 * @brief allocateArray .. returns allocate(elementSize * elementCount)
 * @param elementSize ..  size of an element that will be stored in the array
 * @param elementCount .. number of elements to be stored in the array
 * @return part of memory that is about to be used, NULL if theres insufficient memory
 */
void *allocateArray(size_t elementSize, size_t elementCount);

/**
 * @brief allocateOuterArray .. auxiliary function for allocateArray2D,
 * allocates an array of pointers to arrays, works similalry to allocate function
 * with array length stored in memory preceding counter instead of destructor,
 * also sets memory to 0
 * @param subarrays .. number of pointers to be stored in usable memory
 * @return array of pointers, NULL if insufficient memory
 */
void **allocateOuterArray(size_t subarrays);

/**
 * @brief allocateArray2D
 * @param elementSize
 * @param subarrays
 * @param elementCounts
 * @return
 */
void *allocateArray2D(size_t elementSize, size_t subarrays, size_t *elementCounts);

/**
 * @brief allocateNew
 * @param size
 * @param params
 * @return
 */
void *allocateNew(size_t size, int(*ctor)(void *, void **), void(*dtor)(void *), void **params);

/**
 * @brief acquire
 * @param memory
 * @return
 */
void *acquire(void *memory);

/**
 * @brief acquireArray2D
 * @param array2D
 * @return
 */
void *acquireArray2D(void *array2D);

/**
 * @brief release
 * @param memory
 * @return
 */
int release(void *memory);

/**
 * @brief releaseArray2D
 * @param array2D
 * @return
 */
int releaseArray2D(void *array2D);

#endif /* MEMORYVM_H */
