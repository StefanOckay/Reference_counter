#include "memoryVM.h"
#include "memoryVMObject.h"
#include "memoryVMTests.h"


int main()
{
    test_allocate_zero();
    test_allocate_nonzero();
    test_allocateArray_zero();
    test_allocateArray_nonzero();
    test_allocateArray2D_nonzero_nonNULL();
    test_allocateArray2D_nonzero_NULL();
    test_allocateArray2D_zeroSize_NULL();
    test_allocateArray2D_zeroSubs_NULL();
    test_allocateArray2D_zeros_NULL();
    test_allocateNew_noParams();
    test_allocateNew();
    return 0;
}
