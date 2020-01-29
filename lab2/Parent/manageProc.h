#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <conio.h>
#include <time.h>

void createProc(std::vector<PROCESS_INFORMATION> &procVec, std::vector<HANDLE> &closeEvents, std::vector<HANDLE> &accessEvents);

void closeAllProcs(std::vector<PROCESS_INFORMATION> &procVec, std::vector<HANDLE> &closeEvents, std::vector<HANDLE> &accessEvents);

void closeLastProc(std::vector<PROCESS_INFORMATION> &procVec, std::vector<HANDLE> &closeEvents, std::vector<HANDLE> &accessEvents);

void showMenu();