#pragma warning(disable : 4996)

#include "Salad.h"

Salad::Salad(const char* name, int calories, double cost, double price, eDressingType dressing) :Product(name, calories, cost, price)
{
    this->dressing = dressing;
}

bool Salad::addDressing(eDressingType dressing)
{
    this->dressing = dressing;
    return true;
}

void Salad::toOs(ostream& os) const
{
    os << (int)dressing << " dressing";
}