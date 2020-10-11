#pragma warning(disable : 4996)

#include "Product.h"
#include "utils.h"
#include "IllegalValue.h"

Product::Product(const char* name, int calories, double cost, double price) : name(NULL), cost(DBL_MIN), price(DBL_MAX)
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

const Product& Product::operator=(const Product& other)
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

void Product::setName(const char* name)
{
	if (!isAlphaOnly(name))
		throw IllegalValue("Name");
	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Product::setCalories(int calories)
{
	if (calories < 0)
		throw IllegalValue("Calories");
	this->calories = calories;
}

void Product::setCost(double cost)
{
	if (cost < 0 || cost > price)
		throw IllegalValue("Price");
	this->cost = cost;
}
void Product::setPrice(double price)
{
	if (price < 0 || price < cost)
		throw IllegalValue("Price");
	this->price = price;
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