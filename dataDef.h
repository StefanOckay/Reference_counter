#ifndef DATADEF_H
#define DATADEF_H

#include <stdlib.h>
#include <stdio.h>


typedef struct _dataDef0
{
    size_t nbytes;
    int (*ctor)(void *);
    void (*dtor)(void *);
} dataDef0;

typedef struct _dataDef1
{
    size_t nbytes;
    int (*ctor)(void *, void *);
    void (*dtor)(void *);
} dataDef1;

typedef struct _dataDef2
{
    size_t nbytes;
    int (*ctor)(void *, void *, void *);
    void (*dtor)(void *);
} dataDef2;

#endif /* DATADEF_H */
