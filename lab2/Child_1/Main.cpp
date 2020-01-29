#include <string>

#include "Customer.h"

using namespace std;


int main(int argc, char *argv[])
{
	string accessEventID = argv[1];
	accessEventID += " a";
	string closeEventID = argv[1];
	closeEventID += " c";
	HANDLE accessEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, accessEventID.c_str());
	HANDLE CloseEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, closeEventID.c_str());

	do
	{
		if (WaitForSingleObject(CloseEvent, 1) == WAIT_OBJECT_0)
		{
			CloseHandle(accessEvent);
			CloseHandle(CloseEvent);
			return 1;
		}
		if (WaitForSingleObject(accessEvent, 1) == WAIT_OBJECT_0)
		{
			//Sleep(1000);
			string msg = "Child " + string(argv[1]) + " ";
			for (int i = 0; i < msg.length(); i++)
			{
				if (WaitForSingleObject(CloseEvent, 1) == WAIT_OBJECT_0)
				{
					CloseHandle(CloseEvent);
					CloseHandle(accessEvent);
					return 0;
				}
				cout << msg[i];
				Sleep(50);
			}
			ResetEvent(accessEvent);
		}	
	} while (true);
	return 0;
}

