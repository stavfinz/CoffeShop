#pragma warning(disable : 4996)

using namespace std;
#include <iostream>
#include "utils.h"

bool isAlphaOnly(const char* str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		char ch = str[i];
		if (!isalpha(ch))
		{
			return false;
		}
	}
	return true;
}

void deleteArray(void** arr, int size, int elemSize)
{
	for (int i = 0; i < size; i++)
	{
		void* elem = arr + (i * elemSize);
		delete elem;
	}
	delete[] arr;
}

void increaseArraySize(void** arr, int numElem, int newSize, int elemSize)
{
	void** tempArr = new void* [newSize];
	memcpy(arr, tempArr, numElem * elemSize);
	std::swap(tempArr, arr);
	delete[] tempArr;
}