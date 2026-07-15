#include "HandleWrapper.h"

HandleWrapper::HandleWrapper(const Proc& handle)
{
	processID = handle.processID;

	processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

	if (processHandle == nullptr)
	{
		printf("Process could not open with all access opening with different access %d", GetLastError());

		processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
	}

	if (processHandle == nullptr)
	{
		printf("Couldnt get handle to process %d", GetLastError());
	}
}

HandleWrapper::HandleWrapper(HandleWrapper&& other) noexcept
	: processHandle(other.processHandle), processID(other.processID)
{
	other.processHandle = nullptr;
	other.processID = 0;
}

HandleWrapper& HandleWrapper::operator=(HandleWrapper&& other) noexcept
{
	if (this != &other)
	{
		if (processHandle != nullptr)
		{
			CloseHandle(processHandle);
		}

		processHandle = other.processHandle;
		processID = other.processID;
		other.processHandle = nullptr;
		other.processID = 0;
	}

	return *this;
}

HandleWrapper::~HandleWrapper()
{
	if (processHandle != nullptr)
	{
		CloseHandle(processHandle);
	}
}

HANDLE HandleWrapper::GetHandle() const
{
	return processHandle;
}
