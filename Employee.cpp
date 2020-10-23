#pragma warning(disable : 4996)

#include <ctime>
#include "Employee.h"
#include "Date.h"
#include "utils.h"
#include "IllegalValue.h"

Employee::Employee(const char* name, const char* phoneNumber, double shiftSalary, const Date& hireDate) : Person(name, phoneNumber), hireDate(hireDate)
{
	if (hireDate > getTodayDate())
		throw IllegalValue("Date can not be greater than today.");
	setShiftSalary(shiftSalary);
}

const Employee& Employee::operator=(const Employee& other)
{
	if (this != &other)
	{
		delete[] name;
		delete[] phoneNumber;
		Person::operator=(other);
		this->hireDate = other.hireDate;
		this->shiftSalary = other.shiftSalary;
	}
	return *this;
}

const Employee& Employee::operator=(Employee&& other)
{
	if (this != &other)
	{
		Person::operator=(std::move(other));
		this->hireDate = other.hireDate;
		this->shiftSalary = other.shiftSalary;
	}
	return *this;
}

bool Employee::operator<(const Employee& other) const
{
	return this->getSeniority() < other.getSeniority();
}

bool Employee::operator>(const Employee& other) const 
{
	return this->getSeniority() > other.getSeniority();
}

void Employee::setShiftSalary(double shiftSalary)
{
	if (shiftSalary <= 0)
	{
		throw IllegalValue("Invalid Shift Salary");
	}
	this->shiftSalary = shiftSalary;
}

void Employee::setHireDate(Date& hireDate)
{
	this->hireDate = hireDate;
}

//	calculate a rough estimate of amount of days from hired date to today
int Employee::getSeniority() const
{
	Date today = getTodayDate();

	int num = (today.getYear() - hireDate.getYear()) * 365 +
			(today.getMonth() - hireDate.getMonth()) * 31 +
			(today.getDay() - hireDate.getDay());

	return num;
}

void Employee::toOs(ostream& os) const
{
	os << ", Salary: " << this->getShiftSalary() << ", Seniority: " << this->getSeniority() << ", Hired date: " << this->hireDate;
}