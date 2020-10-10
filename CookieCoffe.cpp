#pragma warning(disable : 4996)

#include "CookieCoffee.h"
#include "IllegalValue.h"

// ctor
CookieCoffee::CookieCoffee(const Cookie& cookie, const Coffee& coffee, double discountPercent, bool groundCookie)
	: Product(coffee), Coffee(coffee), Cookie(cookie), groundCookie(groundCookie)
{
	setDiscountPercent(discountPercent);
}

// setters
void CookieCoffee::setDiscountPercent(double discountPercent)
{
	if (discountPercent > 100 || discountPercent < 0)
	{
		throw IllegalValue("Discount");
	}
	this->discountPercent = discountPercent;
}

// functions
void CookieCoffee::toOs(ostream& os) const
{
	Cookie::toOs(os);
	Coffee::toOs(os);
	os << (groundCookie ? ", grounded" : "") << ", discount: " << discountPercent << "%";
}