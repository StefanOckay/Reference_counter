#include "memoryVM.h"
#include "memoryVMObject.h"
#include "memoryVMTests.h"


typedef struct _safeLogger
{
    FILE *file;
} safeLogger;

// constructor
int initSafeLogger(void* memory, void* param)
{
    safeLogger *logger = (safeLogger*) memory;
    const char *path   = (const char*) param;
    logger->file = fopen(path, "a");
    return logger->file != NULL;
}

// destructor
void closeSafeLogger(void* memory)
{
    safeLogger *logger = (safeLogger *) memory;
    fclose(logger->file);
}

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
    return 0;
}
