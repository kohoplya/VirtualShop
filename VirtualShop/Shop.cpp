#include <iostream>
#include "Shop.h"
#include "Menu.h"
#include "Input.h"
#include "Window.h"
#include <conio.h>
#include <sstream>

using namespace std;
static const char* ranks[] = { "Employee", "Manager", "Director" };

void Shop::createUser() {
	Menu menu;
	menu.SetWidth(24);
	menu.SetHeight(4);

	menu.AddElement("I'm an employee").AddElement("I'm a client");

	while (1) {
		int choice = menu.Select();

		if (choice == 0) {
			Menu menu;
			menu.SetWidth(40);
			menu.SetHeight(4);

			menu.AddElement("you're a regular employee").AddElement("you're a manager").AddElement("you're a member of the management team");
			while (1) {
				int choice = menu.Select();
				Employee emp;
				emp.userRegister(this->users);
				emp.rank = ranks[choice];

				users.push_back(emp);
				break;
			}
			break;
		}
		if (choice == 1) {
			Menu menu;
			menu.SetWidth(24);
			menu.SetHeight(4);

			menu.AddElement("you're not").AddElement("you're a member of the club");

			while (1) {
				int choice = menu.Select();
				User us;
				us.userRegister(this->users);
				us.vip = choice;

				users.push_back(us);
				break;
			}
			break;
		}
	}
}

User* Shop::searchUser(Input& inp) {
	if (inp.getInput()[0] == 0) return nullptr;

	string inputStr = inp.getInput();
	for (User& user : users)
		if (user.username == inputStr)
			return& user;

	return nullptr;
}

User* Shop::signIn() {
	Window win(50, 5, 5);
	char space = ' ';
	string cleaner(win.GetWidth() - 1, space);
	User* user = nullptr;

	Input inp(win.GetWidth());
	string username, password;

	do {
		inp.customInput(win, "Enter your username: ");
		user = searchUser(inp);
		if (user == nullptr) win.writeText(win.GetY() + 2, "User not found");

	} while (user == nullptr);

	do {
		inp.customInput(win, "Enter password: ");
		if (strcmp(user->password.c_str(), inp.getInput()) != 0) { win.writeText(win.GetY() + 2, "Wrong password"); }

	} while (strcmp(user->password.c_str(), inp.getInput()) != 0);

	return user;
}

void Shop::welcome(User* user) {
	Window win(30, 3, 5);
	GotoXY(win.GetX(), win.GetY() + 1);
	cout << "Welcome, " << user->name << " " << user->lastname;
	if (user->vip) cout << "(VIP)";
	if (user->isEmployee) cout << " " << user->rank;

}

void Shop::printCart(Cart* cart) {
	int h = cart->products.size() * 3 + 2;
	int i = 1;
	int j = 0;
	int discount = 0;
	double total = 0;
	stringstream ss;
	Window win(30, h, 5, 53);

	if (cart->user.isEmployee) 	discount += 10;
	while (cart->user.rank != ranks[j] && cart->user.isEmployee) {
		discount += 10;
		j++;
	}

	for (Product& product : cart->products) {
		GotoXY(win.GetX(), win.GetY() + i); cout << product.count << " - " << product.getName();
		GotoXY(win.GetX() + win.GetWidth() / 2, win.GetY() + i); cout << "|";
		GotoXY(win.GetX() + win.GetWidth() - 3, win.GetY() + i); cout << product.count * product.price;
		GotoXY(win.GetX(), win.GetY() + i + 1); cout << "(" << product.description << ")";
		total += product.count * product.price;
		i += 3;
	}
	double discountedTotal = total - (total * discount / 100);
	GotoXY(win.GetX(), win.GetY() + h - 1); cout << "Total" << "(-" << discount << "%)" << ": " << discountedTotal;
	cart->total = total;
}

void Shop::browse(Cart* cart) {
	while (1) {
		cls();
		welcome(&cart->user);
		if (!cart->getProducts().empty()) printCart(cart);
		if (!assortment(cart)) return;
	}

}

bool Shop::checkIsDigit(Input& inp) {
	if (inp.getInput()[0] == 0) return false;

	for (int i = 0; inp.getInput()[i] != 0; i++) {
		if (!isdigit(inp.getInput()[i]))
			return false;
	}

	if (stoi(inp.getInput()) == 0) return false;
	return true;
}


bool Shop::checkCount(Input& inp, vector<Product> products, int choise)
{
	if (checkIsDigit(inp)) {
		int count = stoi(inp.getInput());
		if (count <= 0 || count > products[choise].count) return false;
		return true;
	}
	return false;
}

int Shop::assortment(Cart* cart) {
	Menu menu;
	menu.SetWidth(30);
	menu.SetHeight(products.size() + 1);
	menu.Move(menu.GetX(), menu.GetY()+4);

	for (Product& p : this->products) {
		stringstream ss;
		ss << p.name << " " << p.price;
		menu.AddElement(ss.str().c_str());
	}
	int choise = menu.Select();
	if (choise == -1) {
		cart->user.total += cart->total;
		return 0;
	}

	cls();
	if (this->products[choise].count == 0) {
		Window win(50, 5, 5);
		win.writeText(win.GetY() + 1, "No product in stock, type anything");
		_getch();
	}
	else {
		Window win(50, 5, 5);
		GotoXY(win.GetX(), win.GetY() + 1); cout << "Count in stock: " << this->products[choise].count;
		Input inp(win.GetWidth());
		do {
			inp.customInput(win, "Enter the count: ", 2);
			if (!checkCount(inp, this->products, choise)) { win.writeText(win.GetY() + 3, "Wrong count"); }

		} while (!checkCount(inp, this->products, choise));

		int count = stoi(inp.getInput());

		Product p(this->products[choise]);
		p.count = count;
		cart->products.push_back(p);

		this->products[choise].count -= count;
	}

	return 1;
}

void Shop::printClients(int par) {
	cls();

	Window win(30, users.size() * 3 + 2, 5);
	int i = 0;
	
	for (User& u : users) {
		if ((par == 1 && u.vip) || !par || (par == 2 && u.total > 0)) {
			stringstream ss;
			win.writeText(win.GetY() + 1 + i, u.username);
			ss << u.name << " " << u.lastname << " " << u.total;
			win.writeText(win.GetY() + 2 + i, ss.str());
			i += 3;
		}
	}

	GotoXY(win.GetX(), win.GetY() + win.GetHeight() - 1); cout << "Type anything to exit";
	_getch();
}

void Shop::printBestClients() {
	double maxTotal = 0;
	User* maxTotalUser = nullptr;

	for (User& u : users) {
		if (u.total > maxTotal) {
			maxTotal = u.total;
			maxTotalUser = &u;
		}
	}

	cls();
	Window win(30, 4, 5);
	if (maxTotalUser != nullptr) {
		stringstream ss;
		win.writeText(win.GetY() + 1, maxTotalUser->username);
		ss << maxTotalUser->name << " " << maxTotalUser->lastname << " | Total spent: " << maxTotalUser->total;
		win.writeText(win.GetY() + 2, ss.str());

	}
	_getch();
}

void Shop::addProduct()
{
	cls();
	Window win(50, 5, 5);

	Input inp(win.GetWidth());
	Product* p = new Product();

	inp.customInput(win, "Enter the name of the pruduct: ");
	if (inp.getInput()[0] != 0) p->name = inp.getInput();
	inp.customInput(win, "Enter the description: ");
	if (inp.getInput()[0] != 0) p->description = inp.getInput();

	do {
		inp.customInput(win, "Enter the price: ");
		if (!checkIsDigit(inp)) { win.writeText(win.GetY() + 2, "Wrong price"); }
	} while (!checkIsDigit(inp));
	p->price = stoi(inp.getInput());

	do {
		inp.customInput(win, "Enter the count: ");
		if (!checkIsDigit(inp)) { win.writeText(win.GetY() + 2, "Wrong count"); }
	} while (!checkIsDigit(inp));
	p->count = stoi(inp.getInput());

	products.push_back(*p);
	delete p;
}

void Shop::employeeMenu(User* user, Cart* cart)
{
	Menu menu;
	menu.SetWidth(30);
	menu.SetHeight(7);
	menu.Move(menu.GetX(), menu.GetY() + 4);
	menu.AddElement("Make a purchase").AddElement("Print all clients").AddElement("Print VIP clients").AddElement("Clients with one purchase").AddElement("Clients with highest amount").AddElement("Add new product");

	while (1) {
		cls();
		welcome(user);
		int choise = menu.Select();

		if (choise == 0) browse(cart);
		if (choise == 1) printClients();
		if (choise == 2) printClients(1);
		if (choise == 3) printClients(2);
		if (choise == 4) printBestClients();
		if (choise == 5) addProduct();

		if (choise == -1) break;
	}
}
