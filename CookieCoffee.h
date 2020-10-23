#ifndef __COOKIECOFFEE_H__
#define __COOKIECOFFEE_H__

using namespace std;
#include <iostream>
#include "Coffee.h"
#include "Cookie.h"

class CookieCoffee : public Cookie, public Coffee
{
private:
	bool groundCookie;
	double discountPercent;

public:
	// ctor
	CookieCoffee(const Cookie& cookie, const Coffee& coffee, double discountPercent = 0, bool groundCookie = false) noexcept(false);

	// clone
	virtual Product* clone() const override { return new CookieCoffee(*this); }

	// getters
	bool isGroundCookie() const { return groundCookie; }
	double getDiscountPercent() const { return discountPercent; }

	// setters
	void setDiscountPercent(double discountPercent) noexcept(false);

	// functions
	virtual void toOs(ostream& os) const override;

	virtual int getCalories() const;
	virtual double getCost() const;
	virtual double getPrice() const;
};

#endif
