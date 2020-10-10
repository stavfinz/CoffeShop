#pragma warning(disable : 4996)

#include "Date.h"

 Date::Date(int day, int month, int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
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

 ostream& operator<<(ostream& os, const Date& date)
 {
	 os << date.getDay() << "/" << date.getMonth() << "/" << date.getYear();
	 return os;
 }


