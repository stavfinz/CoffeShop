#pragma warning(disable : 4996)

#include "Product.h"

Product::Product(const char* name, int calories, double cost, double price)
{
	setName(name);
	setCalories(calories);
	setCost(cost);
	setPrice(price);
}

Product::Product(const Product& other) // not sure if need using setter
{
	setName(other.name);
	setCalories(other.calories);
	setCost(other.cost);
	setPrice(other.price);
}
// move ctor
Product::Product(Product&& other) : name(nullptr)
{
	std::swap(name, other.name);
	calories = other.calories;
	cost = other.cost;
	price = other.price;
}

const Product& Product::operator=(const Product& other) /////// Check This
{
	if (this != &other)
	{
		name = other.name;
		calories = other.calories;
		cost = other.cost;
		price = other.price;
	}
	return *this;
}

// move assignment operator
const Product& Product::operator=(Product&& other)
{
	if (this != &other)
	{
		delete[] name;
		std::swap(name, other.name);
		calories = other.calories;
		cost = other.cost;
		price = other.price;
	}
	return *this;
}

Product:: ~Product()
{
	delete[] name;
}

bool Product::setName(const char* name)
{
	if (!name)
		return false;
	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	return true;
}

bool Product::setCalories(int calories)
{
	if (calories < 0)
		return false;
	this->calories = calories;
	return true;
}
bool Product::setCost(double cost)
{
	if (cost < 0)
		return false;
	this->cost = cost;
	return true;
}
bool Product::setPrice(double price)
{
	if (price < 0)
		return false;
	this->price = price;
	return true;
}
// operators
bool Product::operator==(const Product& other) const
{
	return (strcmp(name, other.name) && calories == other.calories &&
		cost == other.cost && price == other.price);
}

ostream& operator<<(ostream& os, const Product& product)
{
	os << "Product:" << product.name << " Calories: " << product.calories << " Cost: " <<
		product.cost << " Price: " << product.price;
	product.toOs(os);
	return os;
}