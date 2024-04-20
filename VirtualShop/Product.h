#pragma once
#include <string>

using namespace std;

class Product
{
	string name;
	string description;
	unsigned int price;
	unsigned int count;

public:
	friend class Shop;

	Product() {};
	Product(string n, string d, unsigned int p, unsigned int c, bool s = true) : name (n), description(d), price(p), count(c){};

	const char* getName() { return this->name.c_str(); }
};