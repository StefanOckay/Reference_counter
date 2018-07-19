#include "memoryVMObject.h"
#include "memoryVM.h"


void *allocateNew0(size_t size, int(*ctor)(void *), void(*dtor)(void *)) {
    if (size == 0) {
        fprintf(stderr, "Invalid block size: %zu\n", size);
        return NULL;
    }
    size_t range = sizeof(void (*)(void *)) + sizeof(size_t) + size;
    void (**dtor__counter__array)(void *) = malloc(range);
    if (dtor__counter__array == NULL) {
        perror("dtor__counter__array");
        return NULL;
    }
    *dtor__counter__array = dtor;
    size_t *counter__array = (size_t *)(dtor__counter__array + 1);
    void *array = (void *)(counter__array + 1);
    if (!ctor(array)) {
        free(dtor__counter__array);
        return NULL;
    }
    *counter__array = 1;
    return array;
}

void *allocateNew1(size_t size, int(*ctor)(void *, void *), void(*dtor)(void *), void *param1) {
    if (size == 0) {
        fprintf(stderr, "Invalid block size: %zu\n", size);
        return NULL;
    }
    size_t range = sizeof(void (*)(void *)) + sizeof(size_t) + size;
    void (**dtor__counter__array)(void *) = malloc(range);
    if (dtor__counter__array == NULL) {
        perror("dtor__counter__array");
        return NULL;
    }
    *dtor__counter__array = dtor;
    size_t *counter__array = (size_t *)(dtor__counter__array + 1);
    void *array = (void *)(counter__array + 1);
    if (!ctor(array, param1)) {
        free(dtor__counter__array);
        return NULL;
    }
    *counter__array = 1;
    return array;
}

void *allocateNew2(size_t size, int(*ctor)(void *, void *, void *), void(*dtor)(void *), void *param1, void *param2) {
    if (size == 0) {
        fprintf(stderr, "Invalid block size: %zu\n", size);
        return NULL;
    }
    size_t range = sizeof(void (*)(void *)) + sizeof(size_t) + size;
    void (**dtor__counter__array)(void *) = malloc(range);
    if (dtor__counter__array == NULL) {
        perror("dtor__counter__array");
        return NULL;
    }
    *dtor__counter__array = dtor;
    size_t *counter__array = (size_t *)(dtor__counter__array + 1);
    void *array = (void *)(counter__array + 1);
    if (!ctor(array, param1, param2)) {
        free(dtor__counter__array);
        return NULL;
    }
    *counter__array = 1;
    return array;


