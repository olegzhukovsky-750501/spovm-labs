#pragma once

#include <iostream>
#include <string>
#include <limits>

class Customer
{
public:
	Customer();
	~Customer();
private:
	int giveCash() const;
	int inputVegAmount() const;
	int inputVegIndex() const;
	void startChild(const std::string& args) const;
	void openMenu() const;
};