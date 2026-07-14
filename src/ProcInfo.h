#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <vector>
#include <string>


struct Proc
{
	std::string currentProcessName;
	DWORD processID = 0;
	uintptr_t moduleAddress;
};