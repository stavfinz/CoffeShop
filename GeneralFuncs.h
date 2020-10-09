#ifndef __GENERAL_FUNCS_H__
#define __GENERAL_FUNCS_H__

typedef size_t uint;

bool isAlphaOnly(const char* str);
void deleteArray(void** arr, int size, int elemSize);
void increaseArraySize(void** arr, int numElem, int newSize, int elemSize);

#endif