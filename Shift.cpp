#pragma warning(disable : 4996)

#include <iostream>
using namespace std;

#include "Shift.h"

Shift::Shift(double clubDiscountPercent, const Date& shiftDate): shiftDate(shiftDate)
{
	//this->shiftDate = *(new Date(shiftDate)); ///// Probably Wrong
	setClubDiscountPercent(clubDiscountPercent);
	dailyMenuSize = 0;
	dailyMenuMaxSize = 10; //Change to const

	numEmployees = 0;
	employeesMaxSize = 5; //Change to const

	numOrders = 0;
	ordersMaxSize = 50; //Change to const
}

bool Shift::setClubDiscountPercent(double clubDiscountPercent)
{
	if (clubDiscountPercent < 0 || clubDiscountPercent > 100)
		return false;
	this->clubDiscountPercent = clubDiscountPercent;
	return true;
}

bool Shift::addProductToMenu(const Product& product)
{

	return false;
}

bool Shift::addEmployeeToShift(const Employee& employee)
{
	return false;

}

bool Shift::addOrder(const Order& order)
{

	return false;
}

//const Shift::Employee* getShiftManger() const

double Shift::getShiftProfit() const
{
	return 0;
}
ostream& operator<<(ostream& os, const Shift& shift)
{
	return cout;
}
