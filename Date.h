#ifndef __DATE_H__
#define __DATE_H__

using namespace std;
#include <iostream>

class Date {
private:
	int day, month, year;

public:
	// ctor
	Date(int day, int month, int year) noexcept(false);

	// getters
	int getDay() const { return day; }
	int getMonth() const { return month; }
	int getYear() const { return year; }

	// functions
	friend ostream& operator<<(ostream& os, const Date& date);

	bool operator==(const Date& d) const;

	bool operator>(const Date& d) const;

	int getMonthDays(int month, int year);

	bool isLeapYear(int year);

	bool isValid(int day, int month, int year);
};

#endif