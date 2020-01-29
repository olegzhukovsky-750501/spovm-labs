#include "VegetableShop.h"

using namespace std;

VegetableShop::VegetableShop()
{
	initData();
}

VegetableShop::~VegetableShop()
{
	string fName = "dataShop.txt";
	ofstream fout(fName);

	if (!fout)
	{
		cout << "Error opening a file" << endl;
		return;
	}

	if (!(fout << cash << endl))
	{
		cout << "Error writing to file" << endl;
		return;
	}

	for (auto it = vegetables.begin(); it != vegetables.end(); ++it)
	{
		fout << it->getName() << " "
			 << it->getPrice() << " "
			 << it->getAmount() << endl;
	}
}

void VegetableShop::addCash(int cash)
{
	this->cash += cash;
}

void VegetableShop::makeChoice(int argc, char * argv[])
{
	if (argc <= 0 || argc > 3)
	{
		cout << "Error, bad arguments" << endl;
		return;
	}

	if (argv[0] == string("g"))
	{
		addCash(atoi(argv[1]));
	}
	else if (argv[0] == string("a"))
	{
		int answer = buy(atoi(argv[1]), atoi(argv[2]));
		switch (answer)
		{
		case 0: cout << "Thank you for purchasing our vegetables" << endl; break;
		case 1: cout << "Sorry, we don't sell such vegetables" << endl; break;
		case 2: cout << "Not enough money" << endl; break;
		case 3: cout << "We don't have so many vegetables" << endl; break;
		}
	}
	else if (argv[0] == string("s"))
	{
		showAvailable();
	}
	else if (argv[0] == string("c"))
	{
		showCash();
	}
	cin.get();
}

void VegetableShop::showCash() const
{
	cout << "You gave me: " << cash << endl;
}

int VegetableShop::buy(int index, int amount)
{

	if (index >= vegetables.size())
	{
		return 1;
	}
	if (amount*(vegetables[index].getPrice()) > cash)
	{
		return 2;
	}
	if (vegetables[index].getAmount() < amount)
	{
		return 3;
	}
	
	cash -= (vegetables[index].getPrice()) * amount;
	for (int i = 0; i < amount; i++)
	{
		vegetables[index].removeItem();
	}
	return 0;
}

void VegetableShop::showAvailable()
{
	for (auto it = vegetables.begin(); it != vegetables.end(); ++it)
	{
	   cout << it->getName() << ". "
			<< "Index: " << it - vegetables.begin() << ". "
			<< "Price: " << it->getPrice() << ". "
			<< "Amount: " << it->getAmount() << endl;
	}
}

void VegetableShop::initData()
{
	string fName("dataShop.txt");
	ifstream fin(fName);

	if (!fin)
	{
		return;
	}

	if (!(fin >> cash))
	{
		cout << "Error reading file: cash" << endl;
		system("pause");
		return;
	}

	while (true)
	{
		string name;
		if (!(fin >> name))
		{
			return;
		}
		else if (name.length() == 0)
		{
			cout << "Bad data" << endl;
			system("pause");
			return;
		}

		int price;

		if (!(fin >> price))
		{
			cout << "Error reading file: price" << endl;
			system("pause");
			return;
		}
		else if (price < 0)
		{
			cout << "Bad data" << endl;
			system("pause");
			return;
		}

		int amount;

		if (!(fin >> amount))
		{
			cout << "Error reading file: amount" << endl;
			system("pause");
			return;
		}
		else if (amount < 0)
		{
			cout << "Bad data" << endl;
			system("pause");
			return;
		}
		vegetables.push_back(Vegetable(name, price, amount));
	}
}
