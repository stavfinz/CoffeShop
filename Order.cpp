#include <iostream>
using namespace std;

#include "Order.h"
#include "Employee.h"
#include "Customer.h"
#include "GeneralFuncs.h"


Order::Order(const Employee& employee, const Customer& customer) : employee(employee), customer(customer)
{
	this->numItems = 0;
	this->itemsMaxSize = 20;
	this->items = new const Product*[itemsMaxSize];
}

bool Order::addItem(const Product& product)
{
	if (numItems == itemsMaxSize)
	{
		itemsMaxSize *= 2;
		increaseArraySize((void**)items, numItems, itemsMaxSize, sizeof(Product*));
	}
	items[numItems++] = &product;
	return true;
}

int Order::getTotalCalories() const
{
	int totalCalories = 0;
	for (int i = 0; i < numItems; i++)
	{
		//totalCalories += this->items[i].getCalories();  // Check This
	}
	return totalCalories;
}
double Order::getOrderProfit() const
{
	int sumProfit = 0;
	for (int i = 0; i < numItems; i++)
	{
		//sumProfit += (items[i].getPrice() - items[i].getCost()); // Check This
	}
	return sumProfit;
}

ostream& operator<<(ostream& os, const Order& order)
{
	os << "Order, Employee: " << order.getEmployee() << " Profit: " << order.getOrderProfit() << endl;
	return os;
}

