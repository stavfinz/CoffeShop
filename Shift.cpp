#pragma warning(disable : 4996)

#include "Shift.h"
#include "Employee.h"
#include "Customer.h"
#include "Order.h"
#include "Product.h"
#include "utils.h"
#include "IllegalValue.h"

const int DEFAULT_ITEMS_SIZE = 10;
const int DEFUALT_EMPLOYEES_SIZE = 5;
const int DEFAULT_ORDERS_SIZE = 50;

Shift::Shift(double clubDiscountPercent, const Date& shiftDate) :shiftDate(shiftDate)
{
	setClubDiscountPercent(clubDiscountPercent);
	dailyMenuSize = 0;
	dailyMenuMaxSize = DEFAULT_ITEMS_SIZE;
	this->dailyMenu = new Product * [dailyMenuMaxSize];

	numEmployees = 0;
	employeesMaxSize = DEFUALT_EMPLOYEES_SIZE;
	this->employees = new const Employee * [employeesMaxSize];

	numOrders = 0;
	ordersMaxSize = DEFAULT_ORDERS_SIZE;
	this->orders = new Order * [ordersMaxSize];
}

Shift::~Shift()
{
	for (int i = 0; i < dailyMenuSize; i++)
	{
		delete dailyMenu[i];
	}
	delete[] dailyMenu;

	for (int i = 0; i < numOrders; i++)
	{
		delete orders[i];
	}
	delete[] orders;

	delete[] employees;
}

void Shift::setClubDiscountPercent(double clubDiscountPercent)
{
	if (clubDiscountPercent < 0 || clubDiscountPercent > 100)
		throw IllegalValue("Illegal discount precentage.");
	this->clubDiscountPercent = clubDiscountPercent;
}

bool Shift::isProductExists(const Product& product) const
{
	for (int i = 0; i < dailyMenuSize; i++)
	{
		if (*dailyMenu[i] == product)
			return true;
	}
	return false;
}

bool Shift::isEmployeeExists(const Person& employee) const
{
	for (int i = 0; i < numEmployees; i++)
	{
		if (*employees[i] == employee)
			return true;
	}
	return false;
}

bool Shift::addProductToMenu(const Product& product)
{
	if (isProductExists(product))
		return false;
	if (dailyMenuSize == dailyMenuMaxSize)		//	if array is full -> increase it
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
	if (isEmployeeExists(employee))
		return false;
	if (numEmployees == employeesMaxSize)		//	if array is full -> increase it
	{
		employeesMaxSize *= 2;
		const Employee** tempArr = new const Employee * [employeesMaxSize];
		memcpy(tempArr, employees, numEmployees * sizeof(Employee*));
		std::swap(tempArr, employees);
		delete[] tempArr;
	}
	employees[numEmployees++] = &employee;
	return true;
}

bool Shift::addOrder(const Order& order)
{
	if (numOrders == ordersMaxSize)		//	if array is full -> increase it
	{
		ordersMaxSize *= 2;
		Order** tempArr = new Order * [ordersMaxSize];
		memcpy(tempArr, orders, numOrders * sizeof(Order*));
		std::swap(tempArr, orders);
		delete[] tempArr;
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
		int currSeniority = employees[i]->getSeniority();
		if (currSeniority > maxSeniorty)
		{
			maxSeniorty = currSeniority;
			shiftManager = employees[i];
		}
	}
	return shiftManager;
}

double Shift::getShiftProfit() const
{
	double profitSum = 0;
	double temp = 0;

	for (int i = 0; i < numOrders; i++)
	{
		temp = orders[i]->getOrderProfit();

		if (orders[i]->getCustomer().isClubMember())
			temp *= (1 - (clubDiscountPercent / 100));
		profitSum += temp;
	}
	return profitSum;
}

ostream& operator<<(ostream& os, const Shift& shift)
{
	os << "Shift Date: " << *shift.getShiftDate() << ", Profit: " << shift.getShiftProfit();
	return os;
}