#include "functions.h"
#include "CoffeeShop.h"
#include "utils.h"

int main()
{
	
	while (true)
	{
		try
		{
			CoffeeShop shop = initCoffeeShop();
			menu(shop);
			break;
		}
		catch (exception& e)
		{
			cleanBuffer();
			cout << e.what() << endl << "Please try again" << endl << endl;
		}
	}
	
	return 0;
}
