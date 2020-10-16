#pragma warning(disable : 4996)

#include "CoffeeShop.h"
#include "Customer.h"
#include "Employee.h"
#include "Shift.h"
#include "Product.h"
#include "Date.h"
#include "utils.h"
#include "IllegalValue.h"

// ctor
CoffeeShop::CoffeeShop(const char* name, const Address& address) : name(nullptr), address(address)
{
	setName(name);

	this->numCustomers = 0;
	this->customersMaxSize = 20;
	this->customers = new Customer*[customersMaxSize];

	this->numEmployees = 0;
	this->employeesMaxSize = 20;
	this->employees = new Employee * [employeesMaxSize];

	this->numShifts = 0;
	this->shiftsMaxSize = 20;
	this->shifts = new Shift * [shiftsMaxSize];

	this->numProducts = 0;
	this->productsMaxSize = 20;
	this->products = new Product * [productsMaxSize];
}

CoffeeShop::CoffeeShop(CoffeeShop&& other) : name(std::move(other.name)), address(std::move(other.address)),
									customers(nullptr), employees(nullptr), shifts(nullptr), products(nullptr)
{
	numCustomers = other.numCustomers;
	customersMaxSize = other.customersMaxSize;
	std::swap(customers, other.customers);

	this->numEmployees = other.numEmployees;
	this->employeesMaxSize = other.employeesMaxSize;
	std::swap(employees, other.employees);

	this->numShifts = other.numShifts;
	this->shiftsMaxSize = other.shiftsMaxSize;
	std::swap(shifts, other.shifts);

	this->numProducts = other.numProducts;
	this->productsMaxSize = other.productsMaxSize;
	std::swap(products, other.products);
}

// dtor
CoffeeShop::~CoffeeShop()
{
	delete[] name;

	for (int i = 0; i < numCustomers; i++)
	{
		delete customers[i];
	}
	delete[]customers;

	for (int i = 0; i < numEmployees; i++)
	{
		delete employees[i];
	}
	delete[]employees;

	for (int i = 0; i < numProducts; i++)
	{
		delete products[i];
	}
	delete[]products;

	for (int i = 0; i < numShifts; i++)
	{
		delete shifts[i];
	}
	delete[]shifts;

	/*deleteArray((void**)customers, numCustomers, sizeof(Customer*));
	deleteArray((void**)employees, numEmployees, sizeof(Employee*));
	deleteArray((void**)shifts, numShifts, sizeof(Shift*));
	deleteArray((void**)products, numProducts, sizeof(Product*));*/
}

// setters
void CoffeeShop::setName(const char* name)
{
	if (strlen(name) < 2)
		throw IllegalValue("Name is too short.");
	if (!isAlphaOnly(name))
		throw IllegalValue("Name should contain characters only.");
	this->name = strdup(name);
}

// functions
bool  CoffeeShop::addNewEmployee(const Employee& employee)
{
	if (numEmployees == employeesMaxSize)
	{
		employeesMaxSize *= 2;
		Employee** tempArr = new Employee * [employeesMaxSize];
		memcpy(tempArr,employees, numEmployees * sizeof(Employee*));
		std::swap(tempArr, employees);
		delete[] tempArr;
		//increaseArraySize((void**)employees, numEmployees, employeesMaxSize, sizeof(Employee*));
	}

	employees[numEmployees++] = new Employee(employee);

	return true;								//	todo: add validations?
}

bool  CoffeeShop::addNewEmployee(Employee&& employee)
{
	if (numEmployees == employeesMaxSize)
	{
		employeesMaxSize *= 2;
		Employee** tempArr = new Employee * [employeesMaxSize];
		memcpy(tempArr,employees, numEmployees * sizeof(Employee*));
		std::swap(tempArr, employees);
		delete[] tempArr;
		//increaseArraySize((void**)employees, numEmployees, employeesMaxSize, sizeof(Employee*));
	}

	employees[numEmployees++] = new Employee(std::move(employee));

	return true;								//	todo: add validations?
}

bool  CoffeeShop::addNewProduct(const Product& product)
{
	if (numProducts == productsMaxSize)
	{
		productsMaxSize *= 2;
		Product** tempArr = new Product * [productsMaxSize];
		memcpy(tempArr, products, numProducts * sizeof(Product*));
		std::swap(tempArr, products);
		delete[] tempArr;
		//increaseArraySize((void**)products, numProducts, productsMaxSize, sizeof(Product*));
	}

	products[numProducts++] = product.clone();

	return true;								//	todo: add validations?
}

bool  CoffeeShop::addNewProduct(Product&& product)
{
	if (numProducts == productsMaxSize)
	{
		productsMaxSize *= 2;
		Product** tempArr = new Product * [productsMaxSize];
		memcpy(tempArr, products, numProducts * sizeof(Product*));
		std::swap(tempArr, products);
		delete[] tempArr;
		//increaseArraySize((void**)products, numProducts, productsMaxSize, sizeof(Product*));
	}

	products[numProducts++] = product.clone();			//	todo: possible to use std::move or something similar?

	return true;								//	todo: add validations?
}

bool  CoffeeShop::addNewCustomer(const Customer& customer)
{
	if (numCustomers == customersMaxSize)
	{
		customersMaxSize *= 2;
		Customer** tempArr = new Customer * [customersMaxSize];
		memcpy(tempArr, customers, numCustomers * sizeof(Customer*));
		std::swap(tempArr, customers);
		delete[] tempArr;
		//increaseArraySize((void**)customers, numCustomers, customersMaxSize, sizeof(Customer*));
	}

	customers[numCustomers++] = new Customer(customer);

	return true;								//	todo: add validations?
}

bool  CoffeeShop::addNewCustomer(Customer&& customer)
{
	if (numCustomers == customersMaxSize)
	{
		customersMaxSize *= 2;
		Customer** tempArr = new Customer * [customersMaxSize];
		memcpy(tempArr, customers, numCustomers * sizeof(Customer*));
		std::swap(tempArr, customers);
		delete[] tempArr;
		//increaseArraySize((void**)customers, numCustomers, customersMaxSize, sizeof(Customer*));
	}

	customers[numCustomers++] = new Customer(std::move(customer));

	return true;								//	todo: add validations?
}

bool  CoffeeShop::openShift(double clubDiscountPercent, const Date& date)
{
	if (numShifts == shiftsMaxSize)
	{
		shiftsMaxSize *= 2;
		Shift** tempArr = new Shift * [shiftsMaxSize];
		memcpy(tempArr, shifts, numShifts * sizeof(Shift*));
		std::swap(tempArr, shifts);
		delete[] tempArr;
		//increaseArraySize((void**)shifts, numShifts, shiftsMaxSize, sizeof(Shift*));
	}

	shifts[numShifts++] = new Shift(clubDiscountPercent, date);

	return true;								//	todo: add validations?
}

Shift* CoffeeShop::getCurrentShift() const
{
	Date today = getTodayDate();

	for (int i = 0; i < numShifts; i++)
	{
		const Date* d = shifts[i]->getShiftDate();

		if (today == *d)
			return shifts[i];
	}
	return nullptr;
}

ostream& operator<<(ostream& os, const CoffeeShop& coffeeShop)
{
	cout << endl << "Employees:" << endl;
	if (coffeeShop.numEmployees == 0)
		cout << "No employess." << endl;
	for (int i = 0; i < coffeeShop.numEmployees; i++)
	{
		cout << "\t" << *coffeeShop.employees[i] << endl;
	}

	cout << endl << "Products:" << endl;
	if (coffeeShop.numProducts == 0)
		cout << "No products." << endl;
	for (int i = 0; i < coffeeShop.numProducts; i++)
	{
		cout << "\t" << *coffeeShop.products[i] << endl;
	}

	cout << endl << "Customers:" << endl;
	if (coffeeShop.numCustomers == 0)
		cout << "No customers." << endl;
	for (int i = 0; i < coffeeShop.numCustomers; i++)
	{
		cout << "\t" << *coffeeShop.customers[i] << endl;
	}

	cout << endl << "Shifts:" << endl;
	if (coffeeShop.numShifts == 0)
		cout << "No shifts." << endl;
	for (int i = 0; i < coffeeShop.numShifts; i++)
	{
		cout << "\t" << *coffeeShop.shifts[i] << endl;
	}

	return os;
}