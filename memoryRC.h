#ifndef MEMORYRC_H
#define MEMORYRC_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/** This API should make memory management easier as it allocates
 * memory with its reference counter(also desctructor for an object).
 * This can help in cases when it's not clear if the memory is still
 * being used somewhere else, thus if it's to be freed.
 * Memory counter is raised with acquire fncs.
 * A pointer, which is no longer needed, can have it's memory counter
 * decremented with release fncs.
 * If the counter's value reaches zero, the memory will be freed.
 * In short, malloc is replaced with allocate fncs, free is replaced with
 * release fncs and passing pointers is done with acquire fncs.
*/

/**
 * @brief allocate .. memory for use along with reference counter(set to 1) preceding
 * the memory block and pointer to destructor which is NULL in this case in order
 * to unify release function, also sets memory to 0
 * @param size .. bytes to allocate
 * @return part of memory that is about to be used, NULL if there's insufficient memory
 */
void *allocate(size_t size);

/**
 * @brief allocateArray .. returns allocate(elementSize * elementCount)
 * @param elementSize ..  size of an element that will be stored in the array
 * @param elementCount .. number of elements to be stored in the array
 * @return part of memory that is about to be used, NULL if there's insufficient memory
 */
void *allocateArray(size_t elementSize, size_t elementCount);

/**
 * @brief allocateOuterArray .. auxiliary function for allocateArray2D,
 * allocates an array of pointers to arrays, works similalry to allocate function
 * with array length stored in memory preceding counter instead of destructor,
 * also sets memory to 0 and counter to 1
 * @param subarrays .. number of pointers to be stored in the memory
 * @return array of pointers, NULL if insufficient memory
 */
void **allocateOuterArray(size_t subarrays);

/**
 * @brief allocateArray2D .. allocates 2D array with various row sizes,
 * each row is allocated with allocate function, the outer array of pointers
 * is allocated with allocateOuterArray function, the counter is set to 1
 * for each array including the outer array of pointers
 * @param elementSize .. size of an element that will be stored in the array
 * @param subarrays .. number of rows
 * @param elementCounts ..  array of row sizes, elementCounts[i] == subarrays,
 * if elementCounts == NULL for each i
 * @return pointer to the allocated 2D array, NULL if insufficient memory
 */
void *allocateArray2D(size_t elementSize, size_t subarrays, size_t *elementCounts);

/**
 * @brief allocateNew .. allocates memory for an object in the same fashion
 * as an allocate function, but dtor is not NULL this time, the constructor
 * for the object, which should set the memory to 0, is called after the allocation,
 * the object reference counter is set to 1
 * @param size .. of the object to be created
 * @param ctor .. constructor of the object
 * @param dtor .. destructor of the object
 * @param params .. array of parameters handed to the constructor
 * @return pointer to the allocated memory of the object, NULL if insufficient memory
 * or if constructor fails
 */
void *allocateNew(size_t size, int(*ctor)(void *, void **), void(*dtor)(void *), void **params);

/**
 * @brief acquire .. increments the counter associated with the used memory,
 * behaviour of this function is defined only for memory allocated with allocate,
 * allocateArray, allocateOuterArray and allocateNew functions
 * @param memory .. pointer having its counter incremented
 * @return the memory pointer being passed to another pointer
 */
void *acquire(void *memory);

/**
 * @brief acquireArray2D .. increments the counter associated with the array,
 * behaviour of this function is defined only for memory allocated with allocateArray2D
 * @param array2D .. pointer having its counter incremented
 * @return the array pointer being passed to another pointer
 */
void *acquireArray2D(void *array2D);

/**
 * @brief release .. decrements the memory counter. If the counter
 * reaches 0, whole memory block including destr. and counter
 * will be freed. Beahviour is defined only for memory allocated with
 * allocate, allocateArray, allocateOuterArray and allocateNew functions
 * @param memory .. having it's counter decremented
 * @return 0 if the counter reaches zero, non-0 otherwise
 */
int release(void *memory);

/**
 * @brief releaseArray2D .. decrements the memory counter of the outer
 * and all the inner arrays.
 * Behaviour is defined only for the memory allocated with allocateArray2D.
 * If the outer array counter reaches 0, the whole block associated
 * with the outer array will be freed, while some inner arrays can still
 * be pointed to by some other pointers, so those don't have to be freed all.
 * The counters of the inner arrays can't be less than the outer counter,
 * otherwise the final releaseArray2D will fail when releasing memory which is
 * no longer on the heap.
 * @param array2D .. having it's counters decremented
 * @return 0 if the outer counter reaches zero, non-0 otherwise
 */
int releaseArray2D(void *array2D);

#endif /* MEMORYRC_H */
