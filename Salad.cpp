#include <iostream>
using namespace std;

#include "Salad.h"

Salad::Salad(const char* name, int calories, double cost, double price, eDressingType dressing) :Product(name, calories, cost, price)
{
    this->dressing = dressing;
}