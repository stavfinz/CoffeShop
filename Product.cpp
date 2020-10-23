#pragma warning(disable : 4996)

#include "Product.h"
#include "utils.h"
#include "IllegalValue.h"

Product::Product(const char* name, int calories, double cost, double price) : name(NULL), cost(DBL_MIN), price(DBL_MAX)
{																			//	initiate with max and min values because of the setters validation
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
	int nameLen = (int)strlen(name);				//	save name length because needed in more than one place
	if (nameLen < 2)								//	if the name is too short
		throw IllegalValue("Product Name should contain at least 2 characters.");
	if (!isAlphaOnly(name))							//	if the name contains non-alphabetic characters
		throw IllegalValue("Product Name should contain characters only.");
	delete[] this->name;							//	delete previous name
	nameLen++;										//	add to the length one place for '\0'
	this->name = new char[nameLen];
	strcpy(this->name, name);
	this->name[0] = toupper(name[0]);				//	upper case the first letter
}

void Product::setCalories(int calories)
{
	if (calories < 0)								//	calories should be non-negative
		throw IllegalValue("Calories can not be less than 0.");
	this->calories = calories;
}

void Product::addCalories(int amount) noexcept(false)
{
	if (amount < 0)									//	can not add negative amount of calories. should not add zero calories
		throw IllegalValue("Can not add less than 0 calories.");
	setCalories(calories + amount);
}

void Product::setCost(double cost)
{
	if (cost < 0 || cost > price)					//	cost should be positive and less than the price 
		throw IllegalValue("Cost can not be greater than the price.");
	this->cost = cost;
}

void Product::setPrice(double price)
{
	if (price < 0 || price < cost)					//	price should be positive and greater than the cost
		throw IllegalValue("Price can not be less than the cost.");
	this->price = price;
}

// operators
bool Product::operator==(const Product& other) const
{													//	if the name equals and the type of the products
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