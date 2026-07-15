#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <iostream>


class Injector
{
public:
	Injector();
	~Injector();

	bool InjectDLL(HANDLE hProcess, const wchar_t* dllPath);
	bool EjectDLL(DWORD processId, const wchar_t* dllPath);
private:

};

