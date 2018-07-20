#ifndef MEMORYVMOBJECT_H
#define MEMORYVMOBJECT_H

#include <stdlib.h>
#include <stdio.h>


/**
 * @brief allocateNew
 * @param size
 * @param params
 * @return
 */
void *allocateNew(size_t size, int(*ctor)(void *, void **), void(*dtor)(void *), void **params);

#endif /* MEMORYVMOBJECT_H */
