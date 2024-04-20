#include "User.h"
#include "Shop.h"
#include <iostream>
#include "Menu.h"
#include "Input.h"
#include "Window.h"

bool User::checkUsername(vector<User> users, Input& inp) {
	if (inp.getInput()[0] == 0) return false;

	for (User user : users)
		if (strcmp(user.username.c_str(), inp.getInput()) == 0)
			return false;

	return true;
}

bool User::checkIsDigit(Input& inp)
{
	if (inp.getInput()[0] == 0) return false;

	for (int i = 0; inp.getInput()[i] != 0; i++) {
		char c = inp.getInput()[i];
		if (isdigit(c))
			return false;
	}

	return true;
}

bool User::checkPassword(Input& inp) {
	string pass = inp.getInput();

	if (pass.length() < 6) return false;
	return true;
}

void User::userRegister(vector<User> users) {
	Window win(50, 5, 5);
	char space = ' ';
	string cleaner(win.GetWidth() - 1, space);

	Input inp(win.GetWidth());
	string name, lastname, username, password;

	do {
		inp.customInput(win, "Enter your name: ");
		if (!checkIsDigit(inp)) { win.writeText(win.GetY() + 2, "The name must not have any numbers"); }

	} while (!checkIsDigit(inp));
	name = inp.getInput();
	this->name = name;

	do {
		inp.customInput(win, "Enter your lastname: ");
		if (!checkIsDigit(inp)) { win.writeText(win.GetY() + 2, "The lastname must not have any numbers"); }

	} while (!checkIsDigit(inp));
	lastname = inp.getInput();
	this->lastname = lastname;

	do {
		inp.customInput(win, "Enter your username: ");
		if (!checkUsername(users, inp)) { win.writeText(win.GetY() + 2, "The username must be unique"); }

	} while (!checkUsername(users, inp));
	username = inp.getInput();
	this->username = username;

	do {
		inp.customInput(win, "Enter password: ");
		if (!checkPassword(inp)) { win.writeText(win.GetY() + 2, "The password is not reliable, must contain at least six symbols"); }
	} while (!checkPassword(inp));
	password = inp.getInput();
	this->password = password;
}