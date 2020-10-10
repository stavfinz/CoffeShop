#ifndef __UTILS_H__
#define __UTILS_H__

bool isAlphaOnly(const char* str);

void deleteArray(void** arr, int size, int elemSize);

void increaseArraySize(void** arr, int numElem, int newSize, int elemSize);

void cleanBuffer();

#endif // !__UTILS_H__