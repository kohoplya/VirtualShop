#pragma once
#include <string>
#include <vector>
#include "Input.h"
#include "Product.h"


using namespace std;

class User
{
protected:
    string name, lastname, username, password;
    bool vip = false;
    bool isEmployee = false;
    const char* rank = nullptr;
    double total = 0;

public:
    friend class Shop;

    User() {};
    User(string name, string lastname, string username, string password, bool vip = false, bool isEmployee = false, const char* rank= nullptr)
        : name(name), lastname(lastname), username(username), password(password), vip(vip), isEmployee(isEmployee), rank(rank){}

    void userRegister(vector<User> users);
    bool checkUsername(vector<User> users, Input& inp);
    bool checkPassword(Input& inp);
    bool checkIsDigit(Input& inp);

    const char* getRank() { return this->rank; }
    bool getIsEmployee() { return this->isEmployee; }
    bool getVip() { return this->vip; }
};

class Cart {
    User& user;
    vector<Product> products;
    double total = 0;

public:
    friend class Shop;

    Cart();
    Cart(User& user) : user(user) {};

    vector<Product>& getProducts() { return this->products; }
};