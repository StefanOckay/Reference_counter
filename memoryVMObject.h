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

#endif /* MEMORYVMOBJECT_H */
