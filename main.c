#include "memoryRC.h"
#include "memoryRCTests.h"


int main()
{
    test_allocate_zero();
    test_allocate();
    test_allocateArray2D();
    test_allocateArray2D_NULL();
    test_allocateArray2D_zeroSize();
    test_allocateArray2D_zeroSubs();
    test_allocateArray2D_allzeros();
    test_allocateNew_noParams();
    test_allocateNew();
    test_acquire_afterAllocate();
    test_acquire_afterAllocateNew();
    test_acquireArray2D();
    test_release_afterAllocate();
    test_release_afterAllocateNew();
    test_release_afterAllocateAcquire();
    test_release_afterAllocateNewAcquire();
    test_releaseArray2D_afterAllocateArray2D();
    test_releaseArray2D_afterAllocateArray2DAcquireArray2D();
    return 0;
}
