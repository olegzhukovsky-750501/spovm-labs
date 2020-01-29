#pragma once

#include <iostream>
#include <string>
#include <limits>
#include <Windows.h>

class Customer
{
public:
	Customer();
	~Customer();
	
	void openMenu() const;
	void showMessage(char* argv[]) const;
private:
	int giveCash() const;
	int inputVegAmount() const;
	int inputVegIndex() const;
	void startChild(const std::string& args) const;
};