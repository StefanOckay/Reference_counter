#include <assert.h>

#include "memoryVM.h"
#include "memoryVMObject.h"


/**
 * @brief initArray
 * @param array
 * @param dims
 * @return
 */
int initArray(void *array, void *dims[2]);

/**
 * @brief freeArray
 * @param array
 */
void freeArray(void *array);

/**
 * @brief test_allocate_zero
 */
void test_allocate_zero();

/**
 * @brief test_allocate
 */
void test_allocate();

/**
 * @brief test_allocateArray2D
 */
void test_allocateArray2D();

/**
 * @brief test_allocateArray2D_NULL
 */
void test_allocateArray2D_NULL();

/**
 * @brief test_allocateArray2D_zeroSize
 */
void test_allocateArray2D_zeroSize();

/**
 * @brief test_allocateArray2D_zeroSubs
 */
void test_allocateArray2D_zeroSubs();

/**
 * @brief test_allocateArray2D_allzeros
 */
void test_allocateArray2D_allzeros();

/**
 * @brief test_allocateNew_noParams
 */
void test_allocateNew_noParams();

/**
 * @brief test_allocateNew
 */
void test_allocateNew();

/**
 * @brief test_acquire_afterAllocate
 */
void test_acquire_afterAllocate();

/**
 * @brief test_acquire_afterAllocateNew
 */
void test_acquire_afterAllocateNew();

/**
 * @brief test_acquireArray2D
 */
void test_acquireArray2D();

/**
 * @brief test_release_afterAllocate
 */
void test_release_afterAllocate();

/**
 * @brief test_release_afterAllocateNew
 */
void test_release_afterAllocateNew();

/**
 * @brief test_release_afterAllocateAcquire
 */
void test_release_afterAllocateAcquire();

/**
 * @brief test_release_afterAllocateNewAcquire
 */
void test_release_afterAllocateNewAcquire();

/**
 * @brief test_releaseArray2D_afterAllocateArray2D
 */
void test_releaseArray2D_afterAllocateArray2D();

/**
 * @brief test_releaseArray2D_afterAllocateArray2DAcquireArray2D
 */
void test_releaseArray2D_afterAllocateArray2DAcquireArray2D();
