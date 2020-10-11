#pragma warning(disable : 4996)

#include "Cookie.h"

Cookie::Cookie(const char* name, int calories, double cost, double price, eFlourType flour) :Product(name, calories, cost, price)
{
    this->flour = flour;
}

void Cookie::toOs(ostream& os) const
{
    os << name << " flour: " << (int)flour;
}