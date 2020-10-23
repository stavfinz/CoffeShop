#pragma warning(disable : 4996)

#include "Date.h"
#include "utils.h"
#include "IllegalValue.h"

Date::Date(int day, int month, int year)
{
	if (!isValid(day, month, year))
	{
		throw IllegalValue("Invalid Date!");
	}

	this->day = day;
	this->month = month;
	this->year = year;
}

bool Date::operator==(const Date& d) const
{
	if (this->year != d.year)		//	if different year
		return false;
	if (this->month != d.month)		//	if different month
		return false;
	if (this->day != d.day)			//	if different day
		return false;
	return true;					//	otherwise, the same
}

bool Date::operator>(const Date& d) const 
{
	if (year <= d.year)				//	if less than or equal year
		return false;
	if (month <= d.month)			//	if less than or equal month
		return false;
	if (day <= d.day)				//	if less than or equal day
		return false;
	return true;					//	otherwise, greater
}

//	get the real amount of days in a month based on the month and the year
int Date::getMonthDays(int month, int year)
{
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	case 2:
		return isLeapYear(year) ? 29 : 28;
	default:
		return -1;
	}
}

//	return true if the year is a leap year, otherwise return false
bool Date::isLeapYear(int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
				return true;
			return false;
		}
		return true;
	}
	return false;
}

// return true if the date is a real valid date
bool Date::isValid(int day, int month, int year)
{
	if (day <= 0 || getMonthDays(month, year) < day)	//	also validate that month is between 1 to 12
		return false;

	if (year < 1900)
		return false;

	return true;
}

ostream& operator<<(ostream& os, const Date& date)
{
	os << date.getDay() << "/" << date.getMonth() << "/" << date.getYear();
	return os;
}
