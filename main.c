#include "memoryVM.h"
#include "memoryVMObject.h"


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
    //void (*f)(void *);
    size_t *counter = malloc(sizeof(void *) + sizeof(size_t));
    *counter = 1;
    printf("counter: %zu\n", *counter);
    void (*f)(void *) = (void *)(counter + 1);
    f = *closeSafeLogger;
    safeLogger logger;
    logger.file = fopen("testfile.txt", "a");
    f(&logger);
    return 0;
    int *array = allocate(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        array[i] = i + 1;
        printf("%i\n", array[i]);
    }
    printf("%zu\n", *((size_t *)array - 1));
    printf("%i\n", array[3]);
    return 0;
}
