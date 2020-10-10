#ifndef __PERSON_H__
#define __PERSON_H__

using namespace std;
#include <iostream>

class Person {
protected:
	char* name, * phoneNumber;

	Person(const Person& other);
	Person(Person&& other);

	const Person& operator=(const Person& other);
	const Person& operator=(Person&& other);

private:
	void setName(const char* name) noexcept(false);

public:
	// ctor
	Person(const char* name, const char* phoneNumber) noexcept(false);

	// dtor
	virtual ~Person();

	// operators
	virtual bool operator==(const Person& other) const;

	// getters
	const char* getName() const { return name; }
	const char* getPhoneNumber() const { return phoneNumber; }

	// setters
	void setPhoneNumber(const char* phoneNumber) noexcept(false);

	// functions
	virtual void toOs(ostream& os) const = 0;
	friend ostream& operator<<(ostream& os, const Person& person);
};

#endif