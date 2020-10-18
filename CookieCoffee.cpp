#pragma warning(disable : 4996)

#include "CookieCoffee.h"
#include "IllegalValue.h"

// ctor
CookieCoffee::CookieCoffee(const Cookie& cookie, const Coffee& coffee, double discountPercent, bool groundCookie)
	: Product(coffee), Coffee(coffee), Cookie(cookie), groundCookie(groundCookie)
{
	setDiscountPercent(discountPercent);

	char name[CHAR_MAX];							//	combined the name of the cookie and the coffee
	strcpy(name, cookie.getName());					//	copy the name of the cookie
	name[strlen(cookie.getName())] = ' ';			//	
	name[strlen(cookie.getName()) + 1] = '\0';		//
	strcat(name, coffee.getName());					//	copy the name of the coffe
	Product::setName(name);
}

// setters
void CookieCoffee::setDiscountPercent(double discountPercent)
{
	if (discountPercent > 100 || discountPercent < 0)
	{
		throw IllegalValue("Illegal Discount.");
	}
	this->discountPercent = discountPercent;
}

int CookieCoffee::getCalories() const
{
	return Coffee::getCalories() + Cookie::getCalories();
}

double CookieCoffee::getCost() const
{
	return Coffee::getCost() + Cookie::getCost();
}

//	the price of the cookie and the coffee minus the discount precentage
double CookieCoffee::getPrice() const
{	
	double price = Coffee::getPrice() + Cookie::getPrice();
	price -= price * discountPercent;
	return price;
}

// functions
void CookieCoffee::toOs(ostream& os) const
{
	Cookie::toOs(os);
	Coffee::toOs(os);
	os << (groundCookie ? ", grounded" : "") << ", discount: " << discountPercent << "%";
}