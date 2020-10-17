#pragma warning(disable : 4996)

#include "Shift.h"
#include "Employee.h"
#include "Order.h"
#include "Product.h"
#include "utils.h"
#include "IllegalValue.h"

Shift::Shift(double clubDiscountPercent, const Date& shiftDate) :shiftDate(shiftDate)
{
	setClubDiscountPercent(clubDiscountPercent);
	dailyMenuSize = 0;
	dailyMenuMaxSize = 10;
	this->dailyMenu = new Product * [dailyMenuMaxSize];

	numEmployees = 0;
	employeesMaxSize = 5;
	this->employees = new const Employee * [employeesMaxSize];

	numOrders = 0;
	ordersMaxSize = 50;
	this->orders = new Order * [ordersMaxSize];
}

Shift::~Shift()
{
	for (int i = 0; i < dailyMenuSize; i++)
	{
		delete dailyMenu[i];
	}
	delete[] dailyMenu;

	for (int i = 0; i < numEmployees; i++)
	{
		delete employees[i];
	}
	delete[] employees;

	for (int i = 0; i < numOrders; i++)
	{
		delete orders[i];
	}
	delete[] orders;

	/*deleteArray((void**)dailyMenu, dailyMenuSize, sizeof(Product*));
	deleteArray((void**)employees, numEmployees, sizeof(Employee*));
	deleteArray((void**)orders, numOrders, sizeof(Order*));*/
}

void Shift::setClubDiscountPercent(double clubDiscountPercent)
{
	if (clubDiscountPercent < 0 || clubDiscountPercent > 100)
		throw IllegalValue("Illegal discount precentage.");
	this->clubDiscountPercent = clubDiscountPercent;
}

bool Shift::addProductToMenu(const Product& product)
{
	for (int i = 0; i < dailyMenuSize; i++)
	{
		if (*dailyMenu[i] == product)
			return false;
	}

	if (dailyMenuSize == dailyMenuMaxSize)
	{
		dailyMenuMaxSize *= 2;
		Product** tempArr = new Product * [dailyMenuMaxSize];
		memcpy(tempArr, dailyMenu, dailyMenuSize * sizeof(Product*));
		std::swap(tempArr, dailyMenu);
		delete[] tempArr;
	}

	dailyMenu[dailyMenuSize++] = product.clone();
	return true;
}

bool Shift::addEmployeeToShift(const Employee& employee)
{
	for (int i = 0; i < numEmployees; i++)
	{
		if (*employees[i] == employee)
			return false;
	}

	if (numEmployees == employeesMaxSize)
	{
		employeesMaxSize *= 2;
		const Employee** tempArr = new const Employee * [employeesMaxSize];
		memcpy(tempArr, employees, numEmployees* sizeof(Employee*));
		std::swap(tempArr, employees);
		delete[] tempArr;
	}

	employees[numEmployees++] = &employee;

	return true;
}

bool Shift::addOrder(const Order& order)
{
	if (numOrders == ordersMaxSize)
	{
		ordersMaxSize *= 2;
		Order** tempArr = new Order * [ordersMaxSize];
		memcpy(tempArr, orders, numOrders * sizeof(Order*));
		std::swap(tempArr, orders);
		delete[] tempArr;
		//increaseArraySize((void**)orders, numOrders, ordersMaxSize, sizeof(Order*));
	}

	orders[numOrders++] = new Order(order);
	return true;
}

const Employee* Shift::getShiftManager() const
{
	int maxSeniorty = 0;
	const Employee* shiftManager = nullptr;
	for (int i = 0; i < numEmployees; i++)
	{
		if (employees[i]->getSeniority() > maxSeniorty)
		{
			maxSeniorty = employees[i]->getSeniority();
			shiftManager = employees[i];
		}
	}
	return shiftManager; //Check This
}

double Shift::getShiftProfit() const
{
	double profitSum = 0;

	for (int i = 0; i < numOrders; i++)
	{
		profitSum += orders[i]->getOrderProfit();
	}
	return profitSum;
}

ostream& operator<<(ostream& os, const Shift& shift)
{
	os << "Shift Date: " << shift.getShiftDate() << " Profit: " << shift.getShiftProfit() << endl;
	return os;
}