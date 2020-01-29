#include <windows.h>
#include <stdio.h>

void main(VOID)
{
	STARTUPINFO StartupInfo;
	//��������� STARTUPINFO ������������ � ��������� CreateProcess,
	//CreateProcessAsUser, CreateProcessWithLogonW, ����� ���������� �������
	//��������, ������� ����, ����������� ���������� � ������� ��� ��������� ����
	//��� ������ ��������.
	PROCESS_INFORMATION ProcInfo;
	// ��������� PROCESS_INFORMATION ����������� �������� CreateProcess �
	// ����������� � ������� ��������� �������� � ��� ��������� ������.
		TCHAR CommandLine[] = TEXT("sleep 6");
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	// Fills a block of memory with zeros.

	StartupInfo.cb = sizeof(StartupInfo);
	ZeroMemory(&ProcInfo, sizeof(ProcInfo));

		if (!CreateProcess(NULL, // �� ������������ ��� ������
			CommandLine, // ��������� ������
			NULL, // ���������� �������� �� �����������.
			NULL, // ���������� ������ �� �����������.
			FALSE, // ��������� ���������� ������������
			0, // ��� ������ �������� ��������
			NULL, // ���� ���������� ��������� ������������� ��������
			NULL, // ������������ ������� ������� ������������� ��������
			&StartupInfo, // ��������� �� ��������� STARTUPINFO.
			&ProcInfo) // ��������� �� ��������� ���������� � ��������.
			)
			printf("CreateProcess failed.");
	// ����� ��������� ��������� ��������
	WaitForSingleObject(ProcInfo.hProcess, INFINITE);
	// ������� ��������� �������� � ������
	CloseHandle(ProcInfo.hProcess);
	CloseHandle(ProcInfo.hThread);
	system("pause");
}