#pragma warning(disable : 4996)

#include <exception>
#include "Coffee.h"

Coffee::Coffee(const char* name, int calories, double cost, double price, bool withMilk, int sugarSpoons) : Product(name, calories, cost, price), sugarSpoons(0)
{
	setMilk(withMilk);
	addSugar(sugarSpoons);
}

const Coffee& Coffee:: operator+=(int sugarSpoons)
{
	this->addSugar(sugarSpoons);
	return *this;
}

void Coffee::addSugar(int sugarSpoons)
{
	if (sugarSpoons < 0)					//	can not add negative amount of spoons
		throw exception("Invalid sugar amount");

	this->sugarSpoons += sugarSpoons;
	addCalories(50 * sugarSpoons);			//	for each spoon add 50 calories
}

void Coffee::setMilk(bool isWithMilk)
{
	this->withMilk = isWithMilk;
	if (isWithMilk)
		addCalories(100);					//	milk should increase the amount of calories
}

void Coffee::toOs(ostream& os) const
{
	os << ", Sugar Spoons: " << this->getSugarSpoons() << (this->getWithMilk() ? ", with milk" : "");
}