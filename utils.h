#ifndef __UTILS_H__
#define __UTILS_H__

using namespace std;
#include <iostream>
#include "Date.h"

static const int SYSTEM_YEAR_FACTOR = 1900;
static const int SYSTEM_MONTH_FACTOR = 1;

bool isAlphaOnly(const char* str);

bool isDigitsOnly(const char* str);

void cleanBuffer();

Date getTodayDate();

Date createDate() noexcept(false);

#endif // !__UTILS_H__