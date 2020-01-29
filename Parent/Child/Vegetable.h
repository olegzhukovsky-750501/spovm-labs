#pragma once

#include <iostream>
#include <string>

class Vegetable
{
public:
	Vegetable(std::string name, int price, int amount);

	void showInfo();
	void removeItem();

	std::string getName();
	int getPrice();
	int getAmount();
private:
	std::string name;
	int price;
	int amount;
};