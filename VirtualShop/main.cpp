#include <iostream>
#include "Menu.h"
#include "Input.h"
#include "Window.h"
#include "Shop.h"

using namespace std;

bool isEmployee(vector<User> users, string username) {
	for (User& user : users)
		if (user.getIsEmployee()) return true;
	return false;
}

void main() {
	Menu menu;
	Shop shop;
	menu.SetWidth(24);
	menu.SetHeight(4);

	menu.AddElement("Create an account").AddElement("Sign in").AddElement("Exit");

	while (1) {
		cls();
		int choice = menu.Select();

		if (choice == 0) {
			shop.createUser();
		}
		if (choice == 1) {
			User* current;
			current = shop.signIn();
			Cart cart(*current);

			cls();
			
			if (current->getRank() == nullptr)
				shop.browse(&cart);
			else
				shop.employeeMenu(current, &cart);
		}
		if (choice == 2) {
			GotoXY(0, 25);
			break;
		}
	}
}