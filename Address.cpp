#pragma warning(disable : 4996)

#include "Address.h"
#include "IllegalValue.h"
#include "utils.h"

Address::Address(const char* city, const char* streetName, int streetNumber) 
{
	setCity(city);
	setStreetName(streetName);
	setStreetNumber(streetNumber);
}

// copy ctor
Address::Address(const Address& other)
{
	*this = other;
}

// move ctor
Address::Address(Address&& other) : city(nullptr), streetName(nullptr)
{
	*this = std::move(other);
}

void Address::setCity(const char* city)
{
	if (!isAlphaOnly(city))
		throw IllegalValue("City");

	this->city = strdup(city);
}

void Address::setStreetName(const char* street)
{
	if (!isAlphaOnly(street))
		throw IllegalValue("Street");

	this->streetName = strdup(street);
}

void Address::setStreetNumber(int num)
{
	if (num <= 0)
	{
		throw IllegalValue("Street Number");
	}
	this->streetNumber = num;
}

// assignment operator
const Address& Address::operator=(const Address& other)
{
	if (this != &other)
	{
		delete[] city;
		delete[] streetName;
		city = strdup(other.city);
		streetName = strdup(other.streetName);
		streetNumber = other.streetNumber;
	}
	return *this;
}

// move assignment operator
const Address& Address::operator=(Address&& other)
{
	if (this != &other)
	{
		std::swap(this->city, other.city);
		std::swap(this->streetName, other.streetName);
		streetNumber = other.streetNumber;
	}
	return *this;
}

// dtor
Address::~Address()
{
	delete[] city;
	delete[] streetName;
}

// functions
ostream& operator<<(ostream& os, const Address& address)
{
	os << address.streetName << " " << address.streetNumber << ", " << address.city << endl;
	return os;
}