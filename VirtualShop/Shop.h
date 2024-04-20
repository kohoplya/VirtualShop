#pragma once

#include <vector>
#include "User.h"
#include "Employee.h"
#include "Product.h"
#include "Input.h"
#include "Window.h"
#include "Menu.h"

class Shop
{
	vector<User> users;
	vector<Product> products;

public:
	Shop() {
		User us("max", "fun", "www", "111111"); 
		User us1("kit", "kat", "wwww", "111111", true);
		User emp("pic", "nic", "ww", "111111", false, true, "Director");
		
		users.push_back(us1);
		users.push_back(us);
		users.push_back(emp);

		Product milk("milk", "cow milk", 5, 20);
		Product sugar("sugar", "white powder", 3, 10);
		Product egg("egg", "bull eggs", 1,  50);
		products.push_back(milk);
		products.push_back(sugar);
		products.push_back(egg);

	}
	void createUser();
	User* searchUser(Input& inp);
	User* signIn();

	bool checkCount(Input& inp, vector<Product> products, int choise);
	bool checkIsDigit(Input& inp);

	void welcome(User* user);
	void printCart(Cart* cart);
	void browse(Cart* cart);
	int assortment(Cart* cart);
	void employeeMenu(User* user, Cart* cart);
	void printClients(int vip = 0);
	void printBestClients();
	void addProduct();

	vector<User>& getUsers() { return this->users; }
	vector<Product>& getProducts() { return this->products; }

};