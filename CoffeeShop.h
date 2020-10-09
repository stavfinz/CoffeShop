#ifndef __COFFEESHOP_H__
#define __COFFEESHOP_H__

#include <iostream>
using namespace std;

#include "Address.h"
class Customer;
class Employee;
class Shift;
class Product;
class Date;

class CoffeeShop {
private:
	char* name;
	Address address;

	int numCustomers, customersMaxSize;
	Customer** customers;

	int numEmployees, employeesMaxSize;
	Employee** employees;

	int numShifts, shiftsMaxSize;
	Shift** shifts;

	int numProducts, productsMaxSize;
	Product** products;
	
public:
	// ctor
	CoffeeShop(const char* name, const Address& address) noexcept(false);
	// copy ctor
	CoffeeShop(const CoffeeShop& other) = delete;
	CoffeeShop(CoffeeShop&& other);

	// move ctor
	//CoffeeShop(const char* name, Address&& address);				//	todo:	not sure about the delete here

	// assignment operator
	const CoffeeShop& operator=(const CoffeeShop& other) = delete;
	// move assignment operator
	const CoffeeShop& operator=(CoffeeShop&& other) = delete;
	// dtor
	~CoffeeShop();

	// getters
	const char* getName() const { return name; }
	int getNumCustomers() const { return numCustomers; }
	int getNumEmployees() const { return numEmployees; }
	int getNumShifts() const { return numShifts; }
	int getNumProducts() const { return numProducts; }
	const Address* getAddress() const { return &address; }
	const Customer* const* getCustomers() const { return customers; }
	const Employee* const* getEmployees() const { return employees; }
	const Shift* const* getShifts() const { return shifts; }
	const Product* const* getProducts() const { return products; }

	// setters
	void setName(const char* name) noexcept(false);
	bool setAddress(const Address& address) noexcept(false) = delete;
	
	// functions
	bool addNewEmployee(const Employee& employee);
	bool addNewEmployee(Employee&& employee);	
	bool addNewProduct(const Product& product);
	bool addNewProduct(Product&& product);
	bool addNewCustomer(const Customer& customer);
	bool addNewCustomer(Customer&& customer);
	bool openShift(double clubDiscountPercent, const Date& date);
	Shift* getCurrentShift() const;
	friend ostream& operator<<(ostream& os, const CoffeeShop& coffeeShop);
};

#endif