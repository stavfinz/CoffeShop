#pragma warning(disable : 4996)

#include <iostream>
using namespace std;

#include "Coffee.h"


Coffee::Coffee(const char* name, int calories, double cost, double price, bool withMilk, int sugarSpoons) : Product(name, calories, cost, price)
{
	this->withMilk = withMilk;
	this->sugarSpoons = sugarSpoons;
}
const Coffee& Coffee:: operator+=(int sugarSpoons)
{
	this->addSugar(sugarSpoons);
	return *this;
}

void Coffee::toOs(ostream& os) const
{
	os << "Sugar Spoons = " << this->getSugarSpoons() << (this->getWithMilk() ? ", with milk" : "") << endl;
}

//Ma laasot kedey she ihtov false?
bool Coffee::addSugar(int sugarSpoons)
{
	this->sugarSpoons += sugarSpoons;
	return true;
}
//Ma laasot kedey she ihtov false?
void Coffee::setMilk(bool isWithMilk)
{
	this->withMilk = isWithMilk;
}