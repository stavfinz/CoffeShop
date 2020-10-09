#include <iostream>
using namespace std;

#include "Date.h"

 Date::Date(int day, int month, int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}

 ostream& operator<<(ostream& os, const Date& date)
 {
	 return os;
 }

 bool Date::operator==(const Date& d)
 {
	 if (this->year != d.year)
		 return false;
	 if (this->month != d.month)
		 return false;
	 if (this->day != d.day)
		 return false;

	 return true;
 }



