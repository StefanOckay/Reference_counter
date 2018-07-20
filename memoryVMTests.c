#include "memoryVMTests.h"


void test_allocate_zero()
{
    int *memory = allocate(0);
    size_t *counter__memory = (size_t *)memory - 1;
    assert(*counter__memory == 1);
    void(**dtor__counter__memory)(void *) = (void(**)(void *))counter__memory - 1;
    assert(*dtor__counter__memory == NULL);
    free(dtor__counter__memory);
    printf("test_allocate_zero: passed\n");
}

void test_allocate_nonzero()
{
    int *memory = allocate(5 * sizeof(int));
    size_t *counter__memory = (size_t *)memory - 1;
    assert(*counter__memory == 1);
    void(**dtor__counter__memory)(void *) = (void(**)(void *))counter__memory - 1;
    assert(*dtor__counter__memory == NULL);
    for(size_t i = 0; i < 5; i++) {
        assert(memory[i] == 0);
    }
    free(dtor__counter__memory);
    printf("test_allocate_nonzero: passed\n");
}

void test_allocateArray_zero()
{
    int *array = allocateArray(0, 5);
    size_t *counter__array = (size_t *)array - 1;
    assert(*counter__array == 1);
    void(**dtor__counter__array)(void *) = (void(**)(void *))counter__array - 1;
    assert(*dtor__counter__array == NULL);
    free(dtor__counter__array);
    printf("test_allocateArray_zero: passed\n");
}

void test_allocateArray_nonzero()
{
    int *array = allocateArray(sizeof(int), 5);
    size_t *counter__array = (size_t *)array - 1;
    assert(*counter__array == 1);
    void(**dtor__counter__array)(void *) = (void(**)(void *))counter__array - 1;
    assert(*dtor__counter__array == NULL);
    for(size_t i = 0; i < 5; i++) {
        assert(array[i] == 0);
    }
    free(dtor__counter__array);
    printf("test_allocateArray_nonzero: passed\n");
}

void test_allocateArray2D_nonzero_nonNULL()
{
    const size_t subarrays = 5;
    size_t counts[subarrays];
    for (size_t i = 0; i < subarrays; i++) {
        counts[i] = i + 1;
    }
    int **array = (int **)allocateArray2D(sizeof(int), subarrays, counts);
    size_t *counter__array = (size_t *)array - 1;
    assert(*counter__array == 1);
    size_t *length__counter__array = counter__array - 1;
    assert(*length__counter__array == subarrays);
    size_t *counter__arrayi;
    void(**dtor__counter__arrayi)(void *);
    for (size_t i = 0; i < subarrays; i++) {
        counter__arrayi = (size_t *)array[i] - 1;
        assert(*counter__arrayi == 1);
        dtor__counter__arrayi = (void(**)(void *))counter__arrayi - 1;
        assert(*dtor__counter__arrayi == NULL);
        for(size_t j = 0; j < counts[i]; j++) {
            assert(array[i][j] == 0);
        }
        free(dtor__counter__arrayi);
    }
    free(length__counter__array);
    printf("test_allocateArray2D_nonzero_nonNULL: passed\n");
}

void test_allocateArray2D_nonzero_NULL()
{
    const size_t subarrays = 5;
    int **array = (int **)allocateArray2D(sizeof(int), subarrays, NULL);
    size_t *counter__array = (size_t *)array - 1;
    assert(*counter__array == 1);
    size_t *length__counter__array = counter__array - 1;
    assert(*length__counter__array == subarrays);
    size_t *counter__array_i;
    void(**dtor__counter__array_i)(void *);
    for (size_t i = 0; i < subarrays; i++) {
        counter__array_i = (size_t *)array[i] - 1;
        assert(*counter__array_i == 1);
        dtor__counter__array_i = (void(**)(void *))counter__array_i - 1;
        assert(*dtor__counter__array_i == NULL);
        for(size_t j = 0; j < subarrays; j++) {
            assert(array[i][j] == 0);
        }
        free(dtor__counter__array_i);
    }
    free(length__counter__array);
    printf("test_allocateArray2D_nonzero_NULL: passed\n");
}

void test_allocateArray2D_zeroSize_NULL()
{
    const size_t subarrays = 5;
    void **array = allocateArray2D(0, subarrays, NULL);
    size_t *counter__array = (size_t *)array - 1;
    assert(*counter__array == 1);
    size_t *length__counter__array = counter__array - 1;
    assert(*length__counter__array == subarrays);
    size_t *counter__array_i;
    void(**dtor__counter__array_i)(void *);
    for (size_t i = 0; i < subarrays; i++) {
        counter__array_i = (size_t *)array[i] - 1;
        assert(*counter__array_i == 1);
        dtor__counter__array_i = (void(**)(void *))counter__array_i - 1;
        assert(*dtor__counter__array_i == NULL);
        free(dtor__counter__array_i);
    }
    free(length__counter__array);
    printf("test_allocateArray2D_zeroSize_NULL: passed\n");
}

void test_allocateArray2D_zeroSubs_NULL()
{
    void **array = allocateArray2D(sizeof(int), 0, NULL);
    size_t *counter__array = (size_t *)array - 1;
    assert(*counter__array == 1);
    size_t *length__counter__array = counter__array - 1;
    assert(*length__counter__array == 0);
    free(length__counter__array);
    printf("test_allocateArray2D_zeroSubs_NULL: passed\n");
}

void test_allocateArray2D_zeros_NULL()
{
    void **array = allocateArray2D(0, 0, NULL);
    size_t *counter__array = (size_t *)array - 1;
    assert(*counter__array == 1);
    size_t *length__counter__array = counter__array - 1;
    assert(*length__counter__array == 0);
    free(length__counter__array);
    printf("test_allocateArray2D_zeros_NULL: passed\n");
}

int initArray(void *array, void *dims[2])
{
    size_t element_size;
    size_t elements;
    if (dims == NULL) {
        element_size = sizeof(int);
        elements = 5;
    } else {
        element_size = *((size_t *) dims[0]);
        elements = *((size_t *) dims[1]);
    }
    memset(array, 0, element_size * elements);
    return 0;
}

void freeArray(void *array)
{
    (void)array;
}

void test_allocateNew_noParams() {
    size_t el_size = sizeof(int);
    size_t els = 5;
    const size_t size = el_size * els;
    int *array = allocateNew(size, initArray, freeArray, NULL);
    for (int i = 0; i < els; i++) {
        assert(array[i] == 0);
    }
    size_t *counter__array = (size_t *)array - 1;
    assert(*counter__array == 1);
    void (**dtor__counter__array)(void *) = (void (**)(void *))counter__array - 1;
    assert(*dtor__counter__array == freeArray);
    free(dtor__counter__array);
    printf("test_allocateNew_noParams: passed\n");
}

void test_allocateNew() {
    void *dims[2];
    size_t el_size = sizeof(int);
    size_t els = 5;
    dims[0] = &el_size;
    dims[1] = &els;
    const size_t size = el_size * els;
    int *array = allocateNew(size, initArray, freeArray, dims);
    for (int i = 0; i < els; i++) {
        assert(array[i] == 0);
    }
    size_t *counter__array = (size_t *)array - 1;
    assert(*counter__array == 1);
    void (**dtor__counter__array)(void *) = (void (**)(void *))counter__array - 1;
    assert(*dtor__counter__array == freeArray);
    free(dtor__counter__array);
    printf("test_allocateNew: passed\n");
}
