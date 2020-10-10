#pragma warning(disable : 4996)

#include <ctime>
#include "CoffeeShop.h"
#include "Customer.h"
#include "Employee.h"
#include "Shift.h"
#include "Product.h"
#include "Date.h"
#include "utils.h"
#include "IllegalValue.h"

// ctor
CoffeeShop::CoffeeShop(const char* name, const Address& address) noexcept(false) : name(nullptr), address(address)
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

	deleteArray((void**)customers, numCustomers, sizeof(Customer*));
	deleteArray((void**)employees, numEmployees, sizeof(Employee*));
	deleteArray((void**)shifts, numShifts, sizeof(Shift*));
	deleteArray((void**)products, numProducts, sizeof(Product*));
}

// setters
void CoffeeShop::setName(const char* name)
{
	if (strlen(name) < 2)
		throw IllegalValue("Name");
	this->name = strdup(name);
}

// functions
bool  CoffeeShop::addNewEmployee(const Employee& employee)
{
	if (numEmployees == employeesMaxSize)
	{
		employeesMaxSize *= 2;
		increaseArraySize((void**)employees, numEmployees, employeesMaxSize, sizeof(Employee*));
	}

	employees[numEmployees++] = new Employee(employee);

	return true;								//	todo: add validations?
}

bool  CoffeeShop::addNewEmployee(Employee&& employee)
{
	if (numEmployees == employeesMaxSize)
	{
		employeesMaxSize *= 2;
		increaseArraySize((void**)employees, numEmployees, employeesMaxSize, sizeof(Employee*));
	}

	employees[numEmployees++] = std::move(&employee);

	return true;								//	todo: add validations?
}

bool  CoffeeShop::addNewProduct(const Product& product)
{
	if (numProducts == productsMaxSize)
	{
		productsMaxSize *= 2;
		increaseArraySize((void**)products, numProducts, productsMaxSize, sizeof(Product*));
	}

	products[numProducts++] = product.clone();

	return true;								//	todo: add validations?
}

bool  CoffeeShop::addNewProduct(Product&& product)
{
	if (numProducts == productsMaxSize)
	{
		productsMaxSize *= 2;
		increaseArraySize((void**)products, numProducts, productsMaxSize, sizeof(Product*));
	}

	products[numProducts++] = std::move(&product);

	return true;								//	todo: add validations?
}

bool  CoffeeShop::addNewCustomer(const Customer& customer)
{
	if (numCustomers == customersMaxSize)
	{
		customersMaxSize *= 2;
		increaseArraySize((void**)customers, numCustomers, customersMaxSize, sizeof(Customer*));
	}

	customers[numCustomers++] = new Customer(customer);

	return true;								//	todo: add validations?
}

bool  CoffeeShop::addNewCustomer(Customer&& customer)
{
	if (numCustomers == customersMaxSize)
	{
		customersMaxSize *= 2;
		increaseArraySize((void**)customers, numCustomers, customersMaxSize, sizeof(Customer*));
	}

	customers[numCustomers++] = &customer;

	return true;								//	todo: add validations?
}

bool  CoffeeShop::openShift(double clubDiscountPercent, const Date& date)
{
	return false;
}

Shift* CoffeeShop::getCurrentShift() const
{
	time_t now = time(0);
	tm* dateStruct = localtime(&now);
	Date today(dateStruct->tm_mday, dateStruct->tm_mon, dateStruct->tm_year);

	for (int i = 0; i < numShifts; i++)
	{
		const Date* d = shifts[i]->getShiftDate();

		if (d == &today)
			return shifts[i];
	}
	delete dateStruct;
	return nullptr;
}

ostream& operator<<(ostream& os, const CoffeeShop& coffeeShop)
{
	cout << "Employees:" << endl;
	for (int i = 0; i < coffeeShop.numEmployees; i++)
	{
		cout << "\t" << coffeeShop.employees[i] << endl;
	}

	cout << endl << "Products:" << endl;
	for (int i = 0; i < coffeeShop.numProducts; i++)
	{
		cout << "\t" << coffeeShop.products[i] << endl;
	}

	cout << endl << "Customers:" << endl;
	for (int i = 0; i < coffeeShop.numCustomers; i++)
	{
		cout << "\t" << coffeeShop.customers[i] << endl;
	}

	cout << endl << "Shifts:" << endl;
	for (int i = 0; i < coffeeShop.numShifts; i++)
	{
		cout << "\t" << coffeeShop.shifts[i] << endl;
	}

	return os;
}