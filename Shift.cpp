#pragma warning(disable : 4996)

#include "Shift.h"
#include "Employee.h"
#include "Order.h"
#include "Product.h"
#include "utils.h"

Shift::Shift(double clubDiscountPercent, const Date& shiftDate) :shiftDate(shiftDate)
{
	setClubDiscountPercent(clubDiscountPercent);
	dailyMenuSize = 0;
	dailyMenuMaxSize = 10; //Change to const
	this->dailyMenu = new Product * [dailyMenuMaxSize];

	numEmployees = 0;
	employeesMaxSize = 5; //Change to const
	this->employees = new Employee * [employeesMaxSize];

	numOrders = 0;
	ordersMaxSize = 50; //Change to const
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

bool Shift::setClubDiscountPercent(double clubDiscountPercent)
{
	if (clubDiscountPercent < 0 || clubDiscountPercent > 100)
		return false;
	this->clubDiscountPercent = clubDiscountPercent;
	return true;
}

bool Shift::addProductToMenu(const Product& product)
{
	if (dailyMenuSize == dailyMenuMaxSize)
		return false;

	dailyMenu[dailyMenuSize++] = product.clone();
	return true;
}

bool Shift::addEmployeeToShift(const Employee& employee)
{
	if (numEmployees == employeesMaxSize)
		return false;
	//employees[numEmployees++] = &employee; ////?????

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

const Employee* Shift::getShiftManger() const
{
	int maxSeniorty = 0;
	Employee* shiftManager = nullptr;
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