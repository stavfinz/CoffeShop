#ifndef __UTILS_H__
#define __UTILS_H__

#include "Date.h"

static const int SYSTEM_YEAR_FACTOR = 1900;
static const int SYSTEM_MONTH_FACTOR = 1;

bool isAlphaOnly(const char* str);

void deleteArray(void** arr, int size, int elemSize);

void increaseArraySize(void** arr, int numElem, int newSize, int elemSize);

void cleanBuffer();

Date getTodayDate();

#endif // !__UTILS_H__