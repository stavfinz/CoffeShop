#pragma warning(disable : 4996)

#include "Customer.h"

// ctor
Customer::Customer(const char* name, const char* phoneNumber, bool clubMember) : Person(name, phoneNumber), clubMember(clubMember)
{
}

Customer::Customer(Customer&& other) : Person(std::move(other)), clubMember(other.clubMember)
{
}

// setters
void Customer::setClubMember(bool clubMember)
{
	this->clubMember = clubMember;
}

// functions
void Customer::toOs(ostream& os) const
{
	os << (clubMember ? ", club member" : "") << endl;
}