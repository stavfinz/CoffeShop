#pragma warning(disable : 4996)

using namespace std;
#include <iostream>
#include <ctime>
#include "utils.h"

bool isAlphaOnly(const char* str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		char ch = str[i];
		if (!isalpha(ch) && ch != ' ')
		{
			return false;
		}
	}
	return true;
}

bool isDigitsOnly(const char* str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}

//void deleteArray(void** arr, int size, int elemSize)		//	todo: fix this functions
//{
//	for (int i = 0; i < size; i++)
//	{
//		void** elem = arr + (i * elemSize);
//		delete *elem;
//	}
//	delete[] arr;
//}
//
//void increaseArraySize(void** arr, int numElem, int newSize, int elemSize)
//{
//	void** tempArr = new void* [newSize];
//	memcpy(tempArr, arr, numElem * elemSize);
//	std::swap(tempArr, arr);
//	delete[] tempArr;
//}

void cleanBuffer()
{
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Date getTodayDate()
{
	time_t now = time(0);
	tm* dateStruct = localtime(&now);
	return Date(dateStruct->tm_mday, dateStruct->tm_mon + SYSTEM_MONTH_FACTOR, dateStruct->tm_year + SYSTEM_YEAR_FACTOR);
}

Date createDate()
{
	int day, month, year;
	cout << "day: " << endl;
	while (!(cin >> day) || day <= 0 || day > 31)
	{
		cleanBuffer();
		cout << "Numbers only, please try again: ";
	}
	cout << "month: " << endl;
	while (!(cin >> month) || month <= 0 || month > 12)
	{
		cleanBuffer();
		cout << "Numbers only, please try again: ";
	}
	cout << "year: " << endl;
	while (!(cin >> year) || year < SYSTEM_YEAR_FACTOR)
	{
		cleanBuffer();
		cout << "Numbers only, please try again: ";
	}

	return Date(day, month, year);
}