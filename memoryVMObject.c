#include "memoryVMObject.h"
#include "memoryVM.h"


void *allocateNew0(dataDef0 *def) {
    if (def->nbytes == 0) {
        fprintf(stderr, "Invalid block size: %zu\n", def->nbytes);
        return NULL;
    }
    size_t size = sizeof(void (*)(void *)) + sizeof(size_t) + def->nbytes;
    void (**dtor__counter__array)(void *) = malloc(size);
    if (dtor__counter__array == NULL) {
        perror("dtor__counter__array");
        return NULL;
    }
    *dtor__counter__array = def->dtor;
    size_t *counter__array = (size_t *)(dtor__counter__array + 1);
    void *array = (void *)(counter__array + 1);
    if (!def->ctor(array)) {
        free(dtor__counter__array);
        return NULL;
    }
    *counter__array = 1;
    return array;
}

void *allocateNew1(dataDef1 *def, void *param1) {
    if (def->nbytes -= 0) {
        fprintf(stderr, "Invalid block size: %zu\n", def->nbytes);
        return NULL;
    }
    size_t size = sizeof(void (*)(void *)) + sizeof(size_t) + def->nbytes;
    void (**dtor__counter__array)(void *) = malloc(size);
    if (dtor__counter__array == NULL) {
        perror("dtor__counter__array");
        return NULL;
    }
    *dtor__counter__array = def->dtor;
    size_t *counter__array = (size_t *)(dtor__counter__array + 1);
    void *array = (void *)(counter__array + 1);
    if (!def->ctor(array, param1)) {
        free(dtor__counter__array);
        return NULL;
    }
    *counter__array = 1;
    return array;
}

void *allocateNew2(dataDef2 *def, void *param1, void *param2) {
    if (def->nbytes == 0) {
        fprintf(stderr, "Invalid block size: %zu\n", def->nbytes);
        return NULL;
    }
    size_t size = sizeof(void (*)(void *)) + sizeof(size_t) + def->nbytes;
    void (**dtor__counter__array)(void *) = malloc(size);
    if (dtor__counter__array == NULL) {
        perror("dtor__counter__array");
        return NULL;
    }
    *dtor__counter__array = def->dtor;
    size_t *counter__array = (size_t *)(dtor__counter__array + 1);
    void *array = (void *)(counter__array + 1);
    if (!def->ctor(array, param1, param2)) {
        free(dtor__counter__array);
        return NULL;
    }
    *counter__array = 1;
    return array;
}

dataDef0 *createDataDef0(size_t size, int(*ctor)(void *), void(*dtor)(void *)) {
    dataDef0 *tmp = allocate(sizeof(dataDef0));
    if (tmp == NULL) {
        return NULL;
    }
    tmp->nbytes = size;
    tmp->ctor = ctor;
    tmp->dtor = dtor;
    return tmp;
}

dataDef1 *createDataDef1(size_t size, int(*ctor)(void *, void *), void(*dtor)(void *)) {
    dataDef1 *tmp = allocate(sizeof(dataDef1));
    if (tmp == NULL) {
        return NULL;
    }
    tmp->nbytes = size;
    tmp->ctor = ctor;
    tmp->dtor = dtor;
    return tmp;
}

dataDef2 *createDataDef2(size_t size, int(*ctor)(void *, void *, void *), void(*dtor)(void *)) {
    dataDef2 *tmp = allocate(sizeof(dataDef2));
    if (tmp == NULL) {
        return NULL;
    }
    tmp->nbytes = size;
    tmp->ctor = ctor;
    tmp->dtor = dtor;
    return tmp;
}

