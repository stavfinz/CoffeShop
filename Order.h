#ifndef __ORDER_H__
#define __ORDER_H__

#include <iostream>
using namespace std;

class Product;
class Employee;
class Customer;

class Order {
private:
	int numItems; // current items in array
	int itemsMaxSize; // current items array max size
	const	Product** items;		// todo: const products??????		/////	

	const Employee& employee;
	const Customer& customer;

	Order(const Order& other);
	const Order& operator=(const Order& other);
	const Order& operator=(Order&& other);
public:
	friend class Shift;
	// ctor
	Order(const Employee& employee, const Customer& customer);		
	// dtor
	~Order();

	// operators
	Order& operator[](int index);
	const Order& operator[](int index) const;
	Order operator+(const Order& order);

	// getters
	int getNumItems() const { return numItems; }
	const Product** getItems() const { return items; }
	const Employee& getEmployee() const { return employee; }
	const Customer& getCustomer() const { return customer; }

	// functions
	bool addItem(const Product& product);
	int getTotalCalories() const;
	double getOrderProfit() const;
	friend ostream& operator<<(ostream& os, const Order& order);
};

#endif
