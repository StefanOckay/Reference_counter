#ifndef MEMORYVMOBJECT_H
#define MEMORYVMOBJECT_H

#include "dataDef.h"


/**
 * @brief allocateNew0
 * @param def
 * @return
 */
void* allocateNew0(dataDef0* def);

/**
 * @brief allocateNew1
 * @param def
 * @param param1
 * @return
 */
void* allocateNew1(dataDef1* def, void* param1);

/**
 * @brief allocateNew2
 * @param def
 * @param param1
 * @param param2
 * @return
 */
void* allocateNew2(dataDef2* def, void* param1, void* param2);

/**
 * @brief createDataDef0
 * @param size
 * @return
 */
dataDef0* createDataDef0(size_t size, int(*ctor)(void*), void(*dtor)(void*));

/**
 * @brief createDataDef1
 * @param size
 * @return
 */
dataDef1* createDataDef1(size_t size, int(*ctor)(void*, void*), void(*dtor)(void*));

/**
 * @brief createDataDef2
 * @param size
 * @return
 */
dataDef2* createDataDef2(size_t size, int(*ctor)(void*, void*, void*), void(*dtor)(void*));

#endif /* MEMORYVMOBJECT_H */
