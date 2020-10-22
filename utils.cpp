#pragma warning(disable : 4996)

using namespace std;
#include <iostream>
#include <ctime>
#include "utils.h"

/// <summary>
/// Checks that a string contains only characters or space
/// </summary>
/// <param name="str">String to check</param>
/// <returns>True if the string contains only characters or a space.</returns>
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

/// <summary>
/// Checks that a string contains only digits
/// </summary>
/// <param name="str">String to check</param>
/// <returns>True if the string contains only digit, false otherwise</returns>
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
//		/*void** elem = arr + (i * elemSize);
//		delete *elem;*/
//		delete arr[i];
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

/// <summary>
/// Create Date object with the date of today
/// </summary>
/// <returns>Date object</returns>
Date getTodayDate()
{
	time_t now = time(0);
	tm* dateStruct = localtime(&now);
	return Date(dateStruct->tm_mday, dateStruct->tm_mon + SYSTEM_MONTH_FACTOR, dateStruct->tm_year + SYSTEM_YEAR_FACTOR);
}

/// <summary>
/// Create a date by users input
/// </summary>
/// <returns>Date object</returns>
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