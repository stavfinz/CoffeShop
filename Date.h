#ifndef __DATE_H__
#define __DATE_H__

using namespace std;
#include <iostream>

class Date {
private:
	int day, month, year;
public:
	// ctor
	Date(int day, int month, int year);

	// getters
	int getDay() const { return day; }
	int getMonth() const { return month; }
	int getYear() const { return year; }

	// functions
	friend ostream& operator<<(ostream& os, const Date& date);

	bool operator==(const Date& d);
};

#endif