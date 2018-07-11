/**
#include "memoryVM.h"
#include "memoryVMObject.h"
**/
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


typedef struct _safeLogger
{
    FILE *file;
} safeLogger;

// constructor
bool initSafeLogger(void* memory, void* param)
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
    printf("ok\n");
}

int main()
{
    void (**f)(void *) = malloc(sizeof(void (*)(void *)) + sizeof(size_t));
    size_t *counter = (size_t *)(f + 1);
    *f = closeSafeLogger;
    safeLogger logger;
    logger.file = fopen("testfile.txt", "a");
    (*f)(&logger);
    *counter = 1;
    printf("counter: %zu\n", *counter);
    return 0;
}
