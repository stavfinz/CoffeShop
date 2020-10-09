#pragma warning(disable : 4996)

#include <iostream>
using namespace std;

#include <ctime>

#include "Employee.h"
#include "Date.h"

Employee::Employee(const char* name, const char* phoneNumber, double shiftSalary, const Date& hireDate) : Person(name, phoneNumber),hireDate(hireDate)
{
	this->shiftSalary = shiftSalary;
}

bool Employee::operator<(const Employee& other)const 
{
	return this->getSeniority() < other.getSeniority();
}

bool Employee::operator>(const Employee& other) const 
{
	return this->getSeniority() > other.getSeniority();
}

/*//Lo barur li ma lirshom po --- Polymorphism?
bool Employee::operator==(const Person& other) const 
{

}*/

bool Employee::setShiftSalary(double shiftSalary)
{
	this->shiftSalary = shiftSalary;
	return true;
}

bool Employee::setHireDate(Date& hireDate)
{
	this->hireDate = hireDate;
	return true;
}

// how to get date of today....
int Employee::getSeniority() const
{
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	std::cout << (now->tm_year + 1900) << '-'
		<< (now->tm_mon + 1) << '-'
		<< now->tm_mday
		<< "\n";
	int num = ((now->tm_year + 1900) - this->hireDate.getYear()) * 365 + 
		((now->tm_mon + 1) - this->hireDate.getMonth()) * 31+
		(now->tm_mday-this->hireDate.getDay());
	
	delete now;

	return num;
}

void Employee::toOs(ostream& os) const
{
	os <<"Salary = "<< this->getShiftSalary() << ", Seniority = "<<this->getSeniority()<< endl;
}