#pragma warning(disable : 4996)

#include "Product.h"
#include "utils.h"
#include "IllegalValue.h"

Product::Product(const char* name, int calories, double cost, double price) : name(NULL), cost(DBL_MIN), price(DBL_MAX)
{																			//	set max and min values first because of the setters validation
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
	int nameLen = (int)strlen(name);
	if (nameLen < 2)
		throw IllegalValue("Product Name should contain at least 2 characters.");
	if (!isAlphaOnly(name))
		throw IllegalValue("Product Name should contain characters only.");
	delete[] this->name;
	nameLen++;	//	one place for '\0'
	this->name = new char[nameLen];
	strcpy(this->name, name);
	this->name[0] = toupper(name[0]);
}

void Product::setCalories(int calories)
{
	if (calories < 0)
		throw IllegalValue("Calories can not be less than 0.");
	this->calories = calories;
}

void Product::addCalories(int amount) noexcept(false)
{
	if (amount < 0)
		throw IllegalValue("Can not add less than 0 calories.");
	setCalories(calories + amount);
}

void Product::setCost(double cost)
{
	if (cost < 0 || cost > price)
		throw IllegalValue("Cost can not be greater than the price.");
	this->cost = cost;
}

void Product::setPrice(double price)
{
	if (price < 0 || price < cost)
		throw IllegalValue("Price can not be less than the cost.");
	this->price = price;
}

// operators
bool Product::operator==(const Product& other) const
{
	return ((strcmp(name, other.name) == 0) && (typeid(*this) == typeid(other)));
}

ostream& operator<<(ostream& os, const Product& product)
{
	os << "(" << typeid(product).name() + 6 << ") " << product.name << " Calories: " <<
		product.calories << " Cost: " <<
		product.cost << " Price: " << product.price;
	product.toOs(os);
	return os;
}