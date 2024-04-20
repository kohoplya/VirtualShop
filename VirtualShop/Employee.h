#pragma once
#include "User.h"

class Employee : public User
{
public:
	Employee() { 
		isEmployee = true;
	};
};