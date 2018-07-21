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

void test_allocate()
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
    printf("test_allocate: passed\n");
}

void test_allocateArray2D()
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
    printf("test_allocateArray2D: passed\n");
}

void test_allocateArray2D_NULL()
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
    printf("test_allocateArray2D_NULL: passed\n");
}

void test_allocateArray2D_zeroSize()
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
    printf("test_allocateArray2D_zeroSize: passed\n");
}

void test_allocateArray2D_zeroSubs()
{
    void **array = allocateArray2D(sizeof(int), 0, NULL);
    size_t *counter__array = (size_t *)array - 1;
    assert(*counter__array == 1);
    size_t *length__counter__array = counter__array - 1;
    assert(*length__counter__array == 0);
    free(length__counter__array);
    printf("test_allocateArray2D_zeroSubs: passed\n");
}

void test_allocateArray2D_allzeros()
{
    void **array = allocateArray2D(0, 0, NULL);
    size_t *counter__array = (size_t *)array - 1;
    assert(*counter__array == 1);
    size_t *length__counter__array = counter__array - 1;
    assert(*length__counter__array == 0);
    free(length__counter__array);
    printf("test_allocateArray2D_allzeros: passed\n");
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
    for (size_t i = 0; i < els; i++) {
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
    int *array = allocateNew(el_size * els, initArray, freeArray, dims);
    for (size_t i = 0; i < els; i++) {
        assert(array[i] == 0);
    }
    size_t *counter__array = (size_t *)array - 1;
    assert(*counter__array == 1);
    void (**dtor__counter__array)(void *) = (void (**)(void *))counter__array - 1;
    assert(*dtor__counter__array == freeArray);
    free(dtor__counter__array);
    printf("test_allocateNew: passed\n");
}

void test_acquire_afterAllocate() {
    size_t size = 5 * sizeof(int);
    void *p1 = allocate(size);
    void *p2 = acquire(p1);
    assert(p1 == p2);
    size_t *counter = (size_t *)p2 - 1;
    assert(*counter == 2);
    void (**dtor)(void *) = (void (**)(void *))counter - 1;
    assert(*dtor == NULL);
    free(dtor);
    printf("test_acquire_afterAllocate: passed(valid only if allocate tests have passed)\n");
}

void test_acquire_afterAllocateNew() {
    void *dims[2];
    size_t el_size = sizeof(int);
    size_t els = 5;
    dims[0] = &el_size;
    dims[1] = &els;
    int *array = allocateNew(el_size * els, initArray, freeArray, dims);
    int *array2 = acquire(array);
    assert(array == array2);
    size_t *counter = (size_t *)array2 - 1;
    assert(*counter == 2);
    void (**dtor)(void *) = (void (**)(void *))counter - 1;
    assert(*dtor == freeArray);
    free(dtor);
    printf("test_acquire_afterAllocateNew: passed(valid only if allocateNew tests have passed)\n");
}

void test_acquireArray2D() {
    const size_t subarrays = 5;
    void **array2D = allocateArray2D(sizeof(int), subarrays, NULL);
    void **array2Dacq = acquireArray2D(array2D);
    assert(array2D == array2Dacq);
    size_t *counter = (size_t *)array2Dacq - 1;
    assert(*counter == 2);
    size_t *len = counter - 1;
    assert(*len == subarrays);
    size_t *counter_i;
    void(**dtor_i)(void *);
    for (size_t i = 0; i < subarrays; i++) {
        counter_i = (size_t *)array2Dacq[i] - 1;
        assert(*counter_i == 2);
        dtor_i = (void(**)(void *))counter_i - 1;
        assert(*dtor_i == NULL);
        free(dtor_i);
    }
    free(len);
    printf("test_acquireArray2D: passed(valid only if allocateArray2D tests have passed)\n");
}

void test_release_afterAllocate() {
    void *memory = allocate(5 * sizeof(int));
    assert(!release(memory));
    printf("test_release_afterAllocate: passed(valid only if allocate tests have passed)\n");
}

void test_release_afterAllocateNew() {
    void *dims[2];
    size_t el_size = sizeof(int);
    size_t els = 5;
    dims[0] = &el_size;
    dims[1] = &els;
    void *memory = allocateNew(el_size * els, initArray, freeArray, dims);
    assert(!release(memory));
    printf("test_release_afterAllocateNew: passed(valid only if allocateNew tests have passed)\n");
}

void test_release_afterAllocateAcquire() {
    void *memory = allocate(5 * sizeof(int));
    void *memory2 = acquire(memory);
    assert(release(memory2));
    size_t *counter = (size_t *)memory - 1;
    assert(*counter == 1);
    void (**dtor)(void *) = (void (**)(void *))counter - 1;
    assert(*dtor == NULL);
    printf("test_release_afterAllocateAcquire: passed(valid only if allocate and acquire tests have passed)\n");
}

void test_release_afterAllocateNewAcquire() {
    void *dims[2];
    size_t el_size = sizeof(int);
    size_t els = 5;
    dims[0] = &el_size;
    dims[1] = &els;
    void *memory = allocateNew(el_size * els, initArray, freeArray, dims);
    void *memory2 = acquire(memory);
    assert(release(memory2));
    size_t *counter = (size_t *)memory - 1;
    assert(*counter == 1);
    void (**dtor)(void *) = (void (**)(void *))counter - 1;
    assert(*dtor == freeArray);
    printf("test_release_afterAllocateNewAcquire: passed(valid only if allocateNew and acquire tests have passed)\n");
}
