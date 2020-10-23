#pragma warning(disable : 4996)

#include "Salad.h"

Salad::Salad(const char* name, int calories, double cost, double price, eDressingType dressing) :Product(name, calories, cost, price)
{
    this->dressing = dressing;
}

void Salad::addDressing(eDressingType dressing)
{
    this->dressing = dressing;
}

void Salad::toOs(ostream& os) const
{
    if (dressing != Salad::eDressingType::enumTypeEnd)      //  if there is a dressing, print it
        os << ", " << sDressingType[(int)dressing] << " dressing";
}