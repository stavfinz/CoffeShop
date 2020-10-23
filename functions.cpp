#include "functions.h"
#include "Salad.h"
#include "Coffee.h"
#include "Cookie.h"
#include "CookieCoffee.h"
#include "Shift.h"
#include "Customer.h"
#include "Employee.h"
#include "Order.h"
#include "CoffeeShop.h"
#include "utils.h"

using namespace std;

const int STRING_SIZE = 255;

CoffeeShop initCoffeeShop()
{
	char name[STRING_SIZE];
	char city[STRING_SIZE], streetName[STRING_SIZE];
	int streetNum;

	// enter coffeeshop details
	cout << "Enter Coffee-Shop name" << endl;
	cin.getline(name, STRING_SIZE);

	cout << "Enter Address details:" << endl;
	cout << "Enter City:" << endl;
	cin.getline(city, STRING_SIZE);

	cout << "Enter Street name:" << endl;
	cin.getline(streetName, STRING_SIZE);

	cout << "Enter Street number:" << endl;
	cin >> streetNum;

	return CoffeeShop(name, Address(city, streetName, streetNum));
}

// coffeeshop menu
void menu(CoffeeShop& shop)
{
	int choice = -1;

	while (choice)
	{
		// get choice from user
		cout << "\nShop Menu" << endl;
		cout << "===============" << endl;
		cout << "Enter your choice:" << endl;
		cout << "1 - Show coffee shop details" << endl;
		cout << "2 - Show employees details" << endl;
		cout << "3 - Show customers details" << endl;
		cout << "4 - Show products details" << endl;
		cout << "5 - Show shifts details" << endl;
		cout << "6 - Add new product to coffee shop" << endl;
		cout << "7 - Add new employee to coffee shop" << endl;
		cout << "8 - Add new customer to coffee shop" << endl;
		cout << "9 - Shift menu" << endl;
		cout << "0 - Quit" << endl;

		if (!(cin >> choice))
			choice = -1;
		cleanBuffer();

		switch (choice)
		{
		case 1:
			// 1. show coffeeshop details
			showCoffeeShop(shop);
			break;
		case 2:
			// 2. show employees details
			showEmployees(shop.getEmployees(), shop.getNumEmployees());
			break;
		case 3:
			// 3. show customers details
			showCustomers(shop.getCustomers(), shop.getNumCustomers());
			break;
		case 4:
			// 4. show products details
			showProducts(shop.getProducts(), shop.getNumProducts());
			break;
		case 5:
			// 5. show shifts details
			showShifts(shop);
			break;
		case 6:
			// 6. add new product to coffee shop
			addProductMenu(shop);
			break;
		case 7:
			// 7. add new employee to coffee shop
			addEmployee(shop);
			break;
		case 8:
			// 8. add new customer to coffee shop
			addCustomer(shop);
			break;
		case 9:
			// 9. shift menu
			shiftMenu(shop);
			break;
		case 0:
			// exit menu
			cout << "Thank you for using the Coffee Shop System, goodbye." << endl;
			return;
		default:
			// show unknown choice msg
			cout << "Invalid choice, try again." << endl;
			break;
		}
	}
}

// return true if shift is still open
void shiftMenu(CoffeeShop& shop)
{
	int choice;
	Shift* shift = nullptr;
	Date* date = nullptr;

	cout << "Open today's shift? Yes=1/No=0: ";
	while (!(cin >> choice))
	{
		cleanBuffer();
		cout << "Invalid choice. Please try again. ";
	}

	if (choice == 1)
		date = new Date(getTodayDate());
	else
	{
		try
		{
			date = new Date(createDate());
		}
		catch (exception& e)
		{
			cout << e.what() << " Please try again." << endl;
			return;
		}
	}

	while (!(shift = shop.getShiftByDate(*date)))
	{
		openShift(shop, *date);
	}

	choice = -1;
	while (choice)
	{
		// get choice from user
		cout << "Shift Menu (" << *date << ")" << endl;
		cout << "===============" << endl;
		cout << "Enter your choice:" << endl;
		cout << "1 - Show daily menu" << endl;
		cout << "2 - Make order" << endl;
		cout << "3 - Add employee to shift" << endl;
		cout << "4 - Add product to dailyMenu" << endl;
		cout << "5 - Show daily profits" << endl;
		cout << "0 - Quit" << endl;

		if (!(cin >> choice))
			choice = -1;
		cleanBuffer();

		switch (choice)
		{
		case 1:
			// 1. show daily menu
			if (shift->getDailyMenuSize() == 0)
				cout << "There are no items in the menu." << endl << endl;
			else
				showProducts(shift->getDailyMenu(), shift->getDailyMenuSize());
			break;
		case 2:
			// 2. make order
			makeOrder(shop, *shift);
			break;
		case 3:
			// 3. add employee to shift
			addEmployeesToShift(shop, *shift);
			break;
		case 4:
			// 4. add product to dailyMenu
			addProductToDailyMenu(shop, *shift);
			break;
		case 5:
			// 5. show daily profits
			showShiftProfits(*shift);
			break;
		case 0:
			return;
		default:
			// show unknown choice msg
			cout << "Invalid choice, try again." << endl;
			break;
		}
	}

	delete date;
}

void openShift(CoffeeShop& shop, const Date& date)
{
	double discount;

	cout << "Enter club discount: " << endl;
	cin >> discount;

	try
	{
		shop.openShift(discount, date);
	}
	catch (exception& e)
	{
		cout << e.what() << " Please try again." << endl;
	}
}

void showCoffeeShop(CoffeeShop& shop)
{
	cout << "The coffee shop details are:" << endl << shop << endl;
}

void showEmployees(const Employee* const* employees, int numEmployees)
{
	cout << "The employees are:" << endl;
	for (int i = 0; i < numEmployees; i++)
	{
		cout << i + 1 << ". " << *employees[i] << endl;
	}
}

void showCustomers(const Customer* const* customers, int numCustomers)
{
	cout << "The customers are:" << endl;
	for (int i = 0; i < numCustomers; i++)
	{
		cout << i + 1 << ". " << *customers[i] << endl;
	}
}

void showProducts(const Product* const* products, int numProducts)
{
	cout << "The products are:" << endl;
	for (int i = 0; i < numProducts; i++)
	{
		cout << i + 1 << ". " << *products[i] << endl;
	}
}

void showShifts(CoffeeShop& shop)
{
	const Shift* const* shifts = shop.getShifts();

	cout << "The shifts of the coffee shop are:" << endl;
	for (int i = 0; i < shop.getNumShifts(); i++)
		cout << i + 1 << ". " << *shifts[i] << endl;
}

const Product* chooseProductByType(CoffeeShop& shop, const type_info& productType)
{
	int choice;
	const Product* const* products = shop.getProducts();
	int numOfProducts = shop.getNumProducts();

	if (numOfProducts == 0)
		return nullptr;

	for (int i = 0; i < numOfProducts; i++)
	{
		if (typeid(*products[i]) == productType)
			cout << i + 1 << ". " << *products[i] << endl;
	}

	while (true)
	{
		cin >> choice;
		cleanBuffer();
		if (choice > 0 && choice <= numOfProducts && productType == typeid(*products[choice - 1]))
			break;				//	break if the choice is in the array bounds and the product's type match
		cout << "Invalid index, please try again." << endl;
	}
	return products[choice - 1];
}

void addProductMenu(CoffeeShop& shop)
{
	int choice = -1;

	while (choice)
	{
		// get choice from user
		cout << "\nChoose product type to add:" << endl;
		cout << "1 - Coffee" << endl;
		cout << "2 - Cookie" << endl;
		cout << "3 - Salad" << endl;
		cout << "4 - CookieCoffee" << endl;
		cout << "0 - Quit" << endl;

		if (!(cin >> choice))
			choice = -1;
		cleanBuffer();

		switch (choice)
		{
		case 1:
			// 1. add coffee product to coffee shop
			addProduct(shop, typeid(Coffee));
			break;
		case 2:
			// 2. add cookie product to coffee shop
			addProduct(shop, typeid(Cookie));
			break;
		case 3:
			// 3. add salad product to coffee shop
			addProduct(shop, typeid(Salad));
			break;
		case 4:
			// 4. add CookieCoffee product to coffee shop
			addCookieCoffee(shop);
			break;
		case 0:
			// exit menu
			return;
		default:
			// show unknown choice msg
			cout << "Invalid choice, try again." << endl;
			break;
		}
	}
}

bool addProduct(CoffeeShop& shop, const type_info& productType)
{
	char name[STRING_SIZE];
	int calories;
	double cost, price;
	int choice;
	bool check = false;

	cout << "Enter product's name: ";
	cin.getline(name, STRING_SIZE);

	cout << "Enter product's calories: ";
	if (!(cin >> calories))
	{
		cleanBuffer();
		cout << "Invalid input." << endl << endl;
		return false;
	}

	cout << "Enter product's cost: ";
	if (!(cin >> cost))
	{
		cleanBuffer();
		cout << "Invalid input." << endl << endl;
		return false;
	}

	cout << "Enter product's price: ";
	if (!(cin >> price))
	{
		cleanBuffer();
		cout << "Invalid input." << endl << endl;
		return false;
	}

	try
	{
		if (productType == typeid(Coffee))
			check = shop.addNewProduct(Coffee(name, calories, cost, price));
		else if (productType == typeid(Salad))
			check = shop.addNewProduct(Salad(name, calories, cost, price));
		else if (productType == typeid(Cookie))
		{
			cout << "Select cookie flour type index" << endl;

			while (true)
			{
				for (int i = 0; i < (int)Cookie::eFlourType::enumTypeEnd; i++)
					cout << i + 1 << ". " << sFlourType[i] << endl;

				if (!(cin >> choice))
					choice = -1;

				if (choice < 1 || choice >(int)Cookie::eFlourType::enumTypeEnd)
					cout << "Invalid choice." << endl;
				else break;
			}

			check = shop.addNewProduct(Cookie(name, calories, cost, price, (Cookie::eFlourType)(choice - 1)));
		}
	}
	catch (exception& e)
	{
		cout << e.what() << " Please try again." << endl;
		return false;
	}

	if (!check)
	{
		cout << "Product already exist in the coffee shop.";
		return false;
	}

	return true;
}

bool addCookieCoffee(CoffeeShop& shop)
{
	const Product* p1, * p2;
	int tmp;
	double discountPercent;
	char choice;

	cout << "Enter product's discount percent:" << endl;
	while (!(cin >> tmp))
	{
		cleanBuffer();
		cout << "Invalid input. Please try again. ";
	}
	discountPercent = (double)tmp / 100;

	cout << "Choose from existing Cookie product:" << endl;
	p1 = chooseProductByType(shop, typeid(Cookie));

	if (p1 == nullptr)
	{
		cout << "There are no Cookies in the menu." << endl;
		return false;
	}

	cout << "Choose from existing Coffee product:" << endl;
	p2 = chooseProductByType(shop, typeid(Coffee));

	if (p2 == nullptr)
	{
		cout << "There is no Coffee in the menu." << endl;
		return false;
	}

	cout << "Would you like to grind the cookie in the coffee? Y/N" << endl;
	cin >> choice;

	bool check = shop.addNewProduct(
		CookieCoffee(
			*dynamic_cast<const Cookie*>(p1),
			*dynamic_cast<const Coffee*>(p2),
			discountPercent,
			(choice == 'Y' || choice == 'y') ? true : false));

	if (!check)
	{
		cout << "Product already exist in the coffee shop.";
		return false;
	}

	return true;
}

void addEmployee(CoffeeShop& shop)
{
	char name[STRING_SIZE];
	char phoneNumber[STRING_SIZE];
	double shiftSalary;
	bool check = false;

	cout << "Enter employee's name" << endl;
	cin.getline(name, STRING_SIZE);

	cout << "Enter employee's phone number" << endl;
	cin.getline(phoneNumber, STRING_SIZE);

	cout << "Enter employee's shift salary" << endl;
	while (!(cin >> shiftSalary))
	{
		cleanBuffer();
		cout << "Numbers only, please enter new salary: ";
	}

	cout << "Enter employee's hire date details: " << endl;

	try
	{
		Date date = createDate();
		check = shop.addNewEmployee(Employee(name, phoneNumber, shiftSalary, date));
	}
	catch (exception& e)
	{
		cout << e.what() << " Please try again." << endl;
		return;
	}

	if (!check)
		cout << "Employee already exist in the coffee shop.";
}

void addCustomer(CoffeeShop& shop)
{
	char name[STRING_SIZE];
	char phoneNumber[STRING_SIZE];
	bool clubMember;
	bool check = false;

	cout << "Enter customer's name" << endl;
	cin.getline(name, STRING_SIZE);

	cout << "Enter customer's phone number" << endl;
	cin.getline(phoneNumber, STRING_SIZE);

	cout << "Is club member? true=1/false=0" << endl;
	while (!(cin >> clubMember))
	{
		cleanBuffer();
		cout << "Invalid input. Please try again. ";
	}

	try
	{
		check = shop.addNewCustomer(Customer(name, phoneNumber, clubMember));
	}
	catch (exception& e)
	{
		cout << e.what() << " Please try again." << endl;
		return;
	}

	if (!check)
		cout << "Customer already exist in the coffee shop.";
}

void makeOrder(CoffeeShop& shop, Shift& shift)
{
	Product* p;
	const Employee* theEmployee;
	const Customer* theCustomer;
	int choice;
	bool withMilk;
	int numOfSugar;

	if (shift.getNumEmployees() == 0)
	{
		cout << "No employees in the shift!" << endl;
		return;
	}

	if (shop.getNumCustomers() == 0)
	{
		cout << "There are no customers in the shop!" << endl;
		return;
	}

	if (shop.getNumProducts() == 0)
	{
		cout << "There are no products in the shop!" << endl;
		return;
	}

	if (shift.getDailyMenuSize() == 0)
	{
		cout << "No products in the daily menu!" << endl;
		return;
	}

	cout << "Enter employee to be incharge of the order" << endl;
	showEmployees(shift.getEmployees(), shift.getNumEmployees());

	while (!(cin >> choice) || choice <= 0 || choice > shift.getNumEmployees())
	{
		cleanBuffer();
		cout << "Invalid index, please try again. ";
	}
	theEmployee = shift.getEmployees()[choice - 1];

	cout << "Enter customer making the order" << endl;
	showCustomers(shop.getCustomers(), shop.getNumCustomers());

	while (!(cin >> choice) || choice <= 0 || choice > shop.getNumCustomers())
	{
		cleanBuffer();
		cout << "Invalid index, please try again. ";
	}
	theCustomer = shop.getCustomers()[choice - 1];

	// create order
	Order theOrder(*theEmployee, *theCustomer);

	cout << "The daily menu items" << endl;
	showProducts(shift.getDailyMenu(), shift.getDailyMenuSize());

	while (choice != -1)
	{
		cout << "choose items indice you wish to order, -1 to stop" << endl;
		if (!(cin >> choice))
			choice = -2;
		cleanBuffer();
		try
		{
			if (choice >= 1 && choice <= shift.getDailyMenuSize())
			{
				p = shift.getDailyMenu()[choice - 1]->clone();
				if (typeid(*p) == typeid(Coffee))
				{
					cout << "With milk? True=1/False=0" << endl;
					cin >> withMilk;
					cout << "How many sugar spoons?" << endl;
					cin >> numOfSugar;
					Coffee* temp = dynamic_cast<Coffee*>(p);
					temp->setMilk(withMilk);
					*temp += numOfSugar;
					p = temp;
				}
				else if (typeid(*p) == typeid(Salad))
				{
					cout << "Select salad dressing type index" << endl;

					while (true)
					{
						for (int i = 0; i < (int)Salad::eDressingType::enumTypeEnd; i++)
							cout << i + 1 << ". " << sDressingType[i] << endl;

						cin >> choice;

						if (choice < 1 || choice >= (int)Salad::eDressingType::enumTypeEnd)
							cout << "Invalid choice" << endl;
						else break;
					}

					Salad* temp = dynamic_cast<Salad*>(p);
					temp->addDressing(Salad::eDressingType(choice - 1));

					p = temp;

				}
				else if (typeid(*p) == typeid(CookieCoffee))
				{
					cout << "With milk? True/False" << endl;
					cin >> withMilk;
					cout << "How many sugar spoons?" << endl;
					cin >> numOfSugar;
					CookieCoffee* temp = dynamic_cast<CookieCoffee*>(p);
					temp->setMilk(withMilk);
					*temp += numOfSugar;
					p = temp;
				}
				else {} // its a cookie

				theOrder += *p;
			}

			else if (choice == -1)
				break;
			else
				cout << "Invalid product index." << endl;
		}
		catch (exception& e)
		{
			cout << e.what() << "Please try again." << endl;
			return;
		}
	}

	shift.addOrder(theOrder);
}

void addEmployeesToShift(CoffeeShop& shop, Shift& shift)
{
	int choice = 1;

	// show all Employees in the coffeeshop
	showEmployees(shop.getEmployees(), shop.getNumEmployees());

	// choose employees to add
	while (choice != -1)
	{
		cout << "choose employee indice you wish to add, -1 to stop" << endl;
		if (!(cin >> choice))
			choice = 0;
		cleanBuffer();

		if (choice >= 1 && choice <= shop.getNumEmployees())
		{
			if (shift.addEmployeeToShift(*shop.getEmployees()[choice - 1]))
			{
				cout << shop.getEmployees()[choice - 1]->getName() << " added to shift! " << endl;
			}
			else
			{
				cout << "Employee already exists in shift!" << endl;
			}
		}
		else if (choice == -1)
			break;
		else
			cout << "Invalid employee index." << endl;
	}
}

void addProductToDailyMenu(CoffeeShop& shop, Shift& shift)
{
	int choice = 1;

	// show all products in the coffeeshop
	showProducts(shop.getProducts(), shop.getNumProducts());

	// choose products to add
	while (choice != -1)
	{
		cout << "choose product indice you wish to add, -1 to stop" << endl;
		if (!(cin >> choice))
			choice = 0;
		cleanBuffer();

		if (choice >= 1 && choice <= shop.getNumProducts())
		{
			if (shift.addProductToMenu(*shop.getProducts()[choice - 1]))
			{
				cout << shop.getProducts()[choice - 1]->getName() << " added to daily menu! " << endl;
			}
			else
			{
				cout << "Product already exists in daily menu!" << endl;
			}
		}
		else if (choice == -1)
			break;
		else
			cout << "Invalid product index" << endl;
	}
}
void showShiftProfits(const Shift& shift)
{
	double total = 0;
	const Order* const* orders = shift.getOrders();
	cout << "Shift Manger: " << *shift.getShiftManager() << endl;
	cout << "Orders: " << endl;
	if (shift.getNumOrders() == 0)
		cout << "There are no orders in this shift." << endl;
	for (int i = 0; i < shift.getNumOrders(); i++)
	{
		cout << (i + 1) << ". " << *orders[i] << endl;
	}
	cout << "Total profits after discount: " << shift.getShiftProfit() << endl << endl;
}