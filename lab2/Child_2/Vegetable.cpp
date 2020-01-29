#include "Vegetable.h"

using namespace std;

Vegetable::Vegetable(std::string name, int price, int amount)
	:name(name), price(price), amount(amount)
{
}

void Vegetable::showInfo()
{
	cout << "Name: " << name << endl
		<< "Price: " << price << endl
		<< "Amount: " << amount << endl;
}

void Vegetable::removeItem()
{
	--amount;
}

std::string Vegetable::getName()
{
	return name;
}

int Vegetable::getPrice()
{
	return price;
}

int Vegetable::getAmount()
{
	return amount;
}
