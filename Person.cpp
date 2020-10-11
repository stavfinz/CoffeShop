#pragma warning(disable : 4996)

#include "Person.h"
#include "utils.h"
#include "IllegalValue.h"

// ctor
Person::Person(const char* name, const char* phoneNumber)
{
	setName(name);
	setPhoneNumber(phoneNumber);
}

Person::Person(const Person& other) :name(NULL), phoneNumber(NULL)
{
	*this = other;
}

Person::Person(Person&& other) : name(NULL), phoneNumber(NULL)
{
	*this = std::move(other);
}

// dtor
Person::~Person()
{
	delete[] this->name;
	delete[] this->phoneNumber;
}

const Person& Person::operator=(const Person& other)
{
	if (this != &other)
	{
		delete[] name;
		delete[] phoneNumber;
		name = strdup(other.name);
		phoneNumber = strdup(other.phoneNumber);
	}
	return *this;
}

const Person& Person::operator=(Person&& other)
{
	if (this != &other)
	{
		std::swap(this->name, other.name);
		std::swap(this->phoneNumber, other.phoneNumber);
	}
	return *this;
}

// operators
bool Person::operator==(const Person& other) const
{
	int nameComp = strcmp(this->name, other.name);
	int phoneComp = strcmp(this->phoneNumber, other.phoneNumber);
	return nameComp == 0 && phoneComp == 0;
}

void Person::setName(const char* name)
{
	if (!isAlphaOnly(name) || strlen(name) < 2)
		throw IllegalValue("Name");

	this->name = strdup(name);
	this->name[0] = toupper(name[0]);
}


void Person::setPhoneNumber(const char* phoneNumber)
{
	int phoneLen = strlen(phoneNumber);
	if (phoneLen < 9)
		throw IllegalValue("Phone Number");
	for (int i = 0; i < phoneLen; i++)
	{
		char ch = phoneNumber[i];
		if (!isdigit(ch) && ch != '-')
		{
			throw IllegalValue("Phone Number");
		}
	}

	this->phoneNumber = strdup(phoneNumber);
}

ostream& operator<<(ostream& os, const Person& person)
{
	os << person.name << ", " << person.phoneNumber;
	person.toOs(os);
	return os;
}