#include "functions.h"
#include "CoffeeShop.h"

int main()
{
	CoffeeShop shop = initCoffeeShop();

	menu(shop);
	
	return 0;
}