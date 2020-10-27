#pragma warning(disable : 4996)

#include <exception>
#include "Person.h"
#include "utils.h"

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
	int nameComp = strcmp(this->name, other.name);					//	compare the names
	int phoneComp = strcmp(this->phoneNumber, other.phoneNumber);	//	compare the phone numbers
	return nameComp == 0 && phoneComp == 0;		//	return true if both equals, false otherwise
}

void Person::setName(const char* name)
{
	if(strlen(name) < 2)						//	if the name is too short
		throw exception("Name should be at least 2 characters.");
	if (!isAlphaOnly(name))						//	if the name contains non-alphabetic characters
		throw exception("Name should be characters only.");

	this->name = strdup(name);
	this->name[0] = toupper(name[0]);			//	upper case the first letter
}


void Person::setPhoneNumber(const char* phoneNumber)
{
	if (strlen(phoneNumber) < 9)				//	if phone number is too short
		throw exception("Phone Number should contain at least 9 digits");
	if (!isDigitsOnly(phoneNumber))				//	if phone number contains non-digits characters
		throw exception("Phone Number");

	this->phoneNumber = strdup(phoneNumber);

}

ostream& operator<<(ostream& os, const Person& person)
{
	os << person.name << ", " << person.phoneNumber;
	person.toOs(os);
	return os;
}