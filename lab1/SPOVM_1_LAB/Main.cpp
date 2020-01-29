#include <windows.h>
#include <stdio.h>

void main(VOID)
{
	STARTUPINFO StartupInfo;
	//Структура STARTUPINFO используется с функциями CreateProcess,
	//CreateProcessAsUser, CreateProcessWithLogonW, чтобы определить оконный
	//терминал, рабочий стол, стандартный дескриптор и внешний вид основного окна
	//для нового процесса.
	PROCESS_INFORMATION ProcInfo;
	// Структура PROCESS_INFORMATION заполняется функцией CreateProcess с
	// информацией о недавно созданном процессе и его первичном потоке.
		TCHAR CommandLine[] = TEXT("sleep 6");
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	// Fills a block of memory with zeros.

	StartupInfo.cb = sizeof(StartupInfo);
	ZeroMemory(&ProcInfo, sizeof(ProcInfo));

		if (!CreateProcess(NULL, // Не используется имя модуля
			CommandLine, // Командная строка
			NULL, // Дескриптор процесса не наследуется.
			NULL, // Дескриптор потока не наследуется.
			FALSE, // Установка описателей наследования
			0, // Нет флагов создания процесса
			NULL, // Блок переменных окружения родительского процесса
			NULL, // Использовать текущий каталог родительского процесса
			&StartupInfo, // Указатель на структуру STARTUPINFO.
			&ProcInfo) // Указатель на структуру информации о процессе.
			)
			printf("CreateProcess failed.");
	// Ждать окончания дочернего процесса
	WaitForSingleObject(ProcInfo.hProcess, INFINITE);
	// Закрыть описатели процесса и потока
	CloseHandle(ProcInfo.hProcess);
	CloseHandle(ProcInfo.hThread);
	system("pause");
}