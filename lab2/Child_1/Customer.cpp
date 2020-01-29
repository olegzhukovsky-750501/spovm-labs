#include <time.h>
#include "Customer.h"

using namespace std;

Customer::Customer()
{
}

Customer::~Customer()
{
}

void Customer::showMessage(char* argv[]) const
{
	cout << argv[0] << " " << argv[1];
}

int Customer::giveCash() const
{
	int cash = 0;
	cout << "Enter the amount of money you want to give to the seller" << endl;
	while (!(cin >> cash) || cash < 0)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Input error, try again" << endl;
	}

	return cash;
}

int Customer::inputVegAmount() const
{
	int amount = 0;
	cout << "Enter amount of vegetables you want to purchase" << endl;
	while (!(cin >> amount) || amount <= 0)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Input error, try again" << endl;
	}

	return amount;
}

int Customer::inputVegIndex() const
{
	int index;
	cout << "Enter index of vegetable you want to buy" << endl;
	while (!(cin >> index) || index < 0)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Input error, try again" << endl;
	}
	return index;
}

void Customer::startChild(const std::string & args) const
{
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION procInfo;

	ZeroMemory(&startupInfo, sizeof(startupInfo));

	startupInfo.cb = sizeof(startupInfo);
	ZeroMemory(&procInfo, sizeof(procInfo));

	if (!CreateProcess(NULL,
		(LPSTR)(("Child_2 " + args).c_str()),
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&startupInfo,
		&procInfo))
	{
		cout << "CreateProcess failed" << endl;
		system("pause");
		return;
	}

	SYSTEMTIME time;
	clock_t begin, end;
	begin = clock();
	while (WaitForSingleObject(procInfo.hProcess, 50))
	{
		
		GetLocalTime(&time);
		printf("Time: %02d:%02d:%02d \r", time.wHour, time.wMinute, time.wSecond);
	}
	end = clock();

	system("CLS");
	cout << "Child process runtime: " << (double)(end - begin) / CLK_TCK << endl;
	system("pause");
	CloseHandle(procInfo.hThread);
	CloseHandle(procInfo.hProcess);
}

void Customer::openMenu() const
{
	while (true)
	{
		bool isCorrect = true;
		string args;
		int a;

		system("CLS");

		cout << "Select action by number" << endl;
		cout << "1. Give money to seller" << endl;
		cout << "2. Ask for vegetables" << endl;
		cout << "3. Show list of vegetables in stock" << endl;
		cout << "4. Check cash" << endl;
		cout << "0. Exit from shop" << endl;

		while(!(cin >> a) || a < 0 || a > 4)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "The entered option doesn't exist or bad input, try again" << endl;
		}

		switch (a)
		{
		case 1:
		{
			args += "g " + to_string(giveCash());
			break;
		}

		case 2:
		{
			args += "a " + to_string(inputVegIndex()) + " " + to_string(inputVegAmount());
			break;
		}
		case 3:
		{
			args += "s";
			break;
		}
		case 4:
		{
			args += "c";
			break;
		}
		case 0:
		{
			return;
		}
		}

		system("CLS");
		
		startChild(args);

		
	}
}

