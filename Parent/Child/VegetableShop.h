#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "Vegetable.h"

class VegetableShop
{
public:
	VegetableShop();
	~VegetableShop();

	void addCash(int cash);
	void makeChoice(int argc, char *argv[]);
	void showCash() const;
	int buy(int index, int amount);
	void showAvailable();
	void initData();
private:

	std::vector<Vegetable> vegetables;
	int cash;
};