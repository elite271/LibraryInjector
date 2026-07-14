#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "ProcInfo.h"

class HandleWrapper
{
public:
	HandleWrapper(const Proc& handle);
	HandleWrapper(const HandleWrapper&) = delete;
	HandleWrapper& operator=(const HandleWrapper&) = delete;
	HandleWrapper(HandleWrapper&&) noexcept;
	HandleWrapper& operator=(HandleWrapper&&) noexcept;
	~HandleWrapper();

	HANDLE GetHandle() const;

private:
	HANDLE processHandle = nullptr;
	DWORD processID = 0;
};