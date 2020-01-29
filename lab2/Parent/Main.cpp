#include "manageProc.h"

using namespace std;

int main()
{
	vector<PROCESS_INFORMATION> procVec;

	vector<HANDLE> closeEvents;

	vector<HANDLE> accessEvents;

	int i = 0;
	char ch;

	showMenu();

	while (true)
	{
		if (!accessEvents.empty() && WaitForSingleObject(accessEvents[i], 1) == WAIT_TIMEOUT)
		{
			if (accessEvents.size() == i + 1) // IF WE STAY AT THE END
			{
				i = 0;  //START FROM BEGIN
			}
			else
			{
				i++;
			}
			SetEvent(accessEvents[i]);
		}
		if (_kbhit())
		{

			char a;
			a = _getch();

			switch (a)
			{
			case '+':
			{
				if (accessEvents.size() == 0)
				{
					i = 0;
				}
				createProc(procVec, closeEvents, accessEvents);
				break;
			}
			case '-':  
			{
				if (procVec.empty())
				{
					cout << "There are no process to close" << endl;
					break;
				}

				while (WaitForSingleObject(accessEvents[i], 1) != WAIT_TIMEOUT); // WAITING FOR THE ENDING PRINT OF THE CURRENT PROCESS

				if (accessEvents.size() == i + 1) //IF WE STAY AT THE END
				{
					i = 0;
					SetEvent(accessEvents[i]);
				}

				closeLastProc(procVec, closeEvents, accessEvents);
				break;
			}
			case 'q':  
			{
				while (!procVec.empty() && WaitForSingleObject(accessEvents[i], 1) != WAIT_TIMEOUT);
				closeAllProcs(procVec, closeEvents, accessEvents); return 0;
			}
			default: break;
			}

		}
		
	}
	
	return 0;
}

void createProc(vector<PROCESS_INFORMATION> &procVec, vector<HANDLE> &closeEvents, vector<HANDLE> &accessEvents)
{
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION procInfo;

	stringstream ss;

	string closeEventID;
	string accessEventID;

	ss << closeEvents.size();
	ss >> closeEventID;
	
	accessEventID = closeEventID + " a";
	string params = "Child_1 " + closeEventID;
	closeEventID += " c";

	ZeroMemory(&startupInfo, sizeof(startupInfo));

	startupInfo.cb = sizeof(startupInfo);
	ZeroMemory(&procInfo, sizeof(procInfo));


	HANDLE closeEvent = CreateEvent(
		NULL,
		TRUE,
		FALSE,
		closeEventID.c_str()
	);

	HANDLE accessEvent = CreateEvent(
		NULL,
		TRUE,
		FALSE,
		accessEventID.c_str()
	);

	closeEvents.push_back(closeEvent);
	accessEvents.push_back(accessEvent);

	if (!CreateProcess(NULL,
		(LPSTR)(params.c_str()),
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&startupInfo,
		&procInfo))
	{
		cout << "CreateProcess failed" << endl;
		system("pause");
		return;
	}

	procVec.push_back(procInfo);

}

void closeLastProc(vector<PROCESS_INFORMATION> &procVec, vector<HANDLE> &closeEvents, vector<HANDLE> &accessEvents)
{

	SetEvent(closeEvents.back());
	CloseHandle(closeEvents.back());
	closeEvents.pop_back();

	WaitForSingleObject(procVec.back().hProcess, INFINITE);

	CloseHandle(procVec.back().hThread);
	CloseHandle(procVec.back().hProcess);

	CloseHandle(accessEvents.back());
	accessEvents.pop_back();
	procVec.pop_back();
}

void closeAllProcs(vector<PROCESS_INFORMATION> &procVec, vector<HANDLE> &closeEvents, vector<HANDLE> &accessEvents)
{
	while (!procVec.empty())
	{
		closeLastProc(procVec, closeEvents, accessEvents);
	}
}

void showMenu()
{
	cout << "Choose your action" << endl;

	cout << "1. Add process. Type '+'" << endl
		<< "2. Delete last created process. Type '-'" << endl
		<< "3. Quit. Type 'q'" << endl;
}