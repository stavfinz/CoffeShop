#pragma warning(disable : 4996)

#include "Product.h"

Product::Product(const char* name, int calories, double cost, double price) : name(NULL)
{
	setName(name);
	setCalories(calories);
	setCost(cost);
	setPrice(price);
}

Product::Product(const Product& other)
{
	*this = other;
}
// move ctor
Product::Product(Product&& other)
{
	*this = std::move(other);
}

const Product& Product::operator=(const Product& other) /////// Check This
{
	if (this != &other)
	{
		if (!name)
			delete[] name;
		name = strdup(other.name);
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
	os << product.name << " Calories: " << product.calories << " Cost: " <<
		product.cost << " Price: " << product.price;
	product.toOs(os);
	return os;
}