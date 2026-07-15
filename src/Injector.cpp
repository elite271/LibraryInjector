#include "Injector.h"

Injector::Injector()
{
}

Injector::~Injector()
{
}

bool Injector::InjectDLL(HANDLE hProcess, const wchar_t* dllPath)
{
	size_t size = (wcslen(dllPath) + 1) * sizeof(wchar_t);

	LPVOID remoteMem = VirtualAllocEx(
		hProcess,
		nullptr,
		size,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_READWRITE
	);

	if (!remoteMem)
	{
		std::cout << "Virtual alloc failed: " << GetLastError() << std::endl;

		return false;
	}

	WriteProcessMemory(
		hProcess,
		remoteMem,
		dllPath,
		size,
		nullptr
	);

	HMODULE hKernel32 = GetModuleHandleW(L"kernel32.dll");
	auto loadLibrary =
		(LPTHREAD_START_ROUTINE)GetProcAddress(
			hKernel32, "LoadLibraryW"
		);

	HANDLE hThread = CreateRemoteThread(
		hProcess,
		nullptr,
		0,
		loadLibrary,
		remoteMem,
		0,
		nullptr
	);

	if (hThread == nullptr)
	{
		std::cout << "Hthread is nullptr: " << GetLastError() << std::endl;

		return false;
	}

	// return hThread != nullptr;
	if (hThread != nullptr)
	{
		CloseHandle(hThread);
	}

	return true;
}

bool Injector::EjectDLL(DWORD processId, const wchar_t* dllPath)
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	if (hProcess == nullptr)
	{
		std::wcerr << "Process Handle is invalid" << std::endl;

		return false;
	}

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hProcess);
		return false;
	}

	MODULEENTRY32W moduleEntry = { sizeof(MODULEENTRY32W) };
	HMODULE hModule = NULL;

	if (Module32FirstW(hSnapshot, &moduleEntry))
	{
		do
		{
			if (_wcsicmp(moduleEntry.szExePath, dllPath) == 0)
			{
				hModule = moduleEntry.hModule;
				break;
			}
		} while (Module32NextW(hSnapshot, &moduleEntry));
	}

	CloseHandle(hSnapshot);

	if (!hModule)
	{
		std::wcerr << L"DLL not found in target process" << std::endl;
		CloseHandle(hProcess);
		return false;
	}

	LPVOID pFreeLibrary = (LPVOID)GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "FreeLibrary");

	HANDLE hThread = CreateRemoteThread(
		hProcess,
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)pFreeLibrary,
		hModule,
		0,
		NULL
	);

	if (!hThread)
	{
		std::wcerr << L"Failed to create eject thread" << GetLastError() << std::endl;
		CloseHandle(hProcess);
		return false;
	}

	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
	CloseHandle(hProcess);

	std::wcout << L"DLL ejected successfully!" << std::endl;
	return true;
}
