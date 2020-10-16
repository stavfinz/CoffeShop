#pragma warning(disable : 4996)

#include "Coffee.h"
#include "IllegalValue.h"

Coffee::Coffee(const char* name, int calories, double cost, double price, bool withMilk, int sugarSpoons) : Product(name, calories, cost, price)
{
	setMilk(withMilk);
	addSugar(sugarSpoons);
}

const Coffee& Coffee:: operator+=(int sugarSpoons)
{
	this->addSugar(sugarSpoons);
	return *this;
}

//Ma laasot kedey she ihtov false?
bool Coffee::addSugar(int sugarSpoons)
{
	if (sugarSpoons < 1)
	{
		throw IllegalValue("Invalid sugar amount");
	}
	this->sugarSpoons += sugarSpoons;
	return true;
}

//Ma laasot kedey she ihtov false?
void Coffee::setMilk(bool isWithMilk)
{
	this->withMilk = isWithMilk;
}

void Coffee::toOs(ostream& os) const
{
	os << ", Sugar Spoons = " << this->getSugarSpoons() << (this->getWithMilk() ? ", with milk" : "");
}