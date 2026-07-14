#include "ProcessList.h"

ProcessList::ProcessList()
{
}

ProcessList::~ProcessList()
{
}

bool ProcessList::init()
{
    return scanForProcesses();
}

bool ProcessList::Refresh()
{
	Clear();
	return this->scanForProcesses();
}

void ProcessList::Clear()
{
	this->processes.clear();
}

Proc ProcessList::at(size_t i)
{
	return this->processes.at(i);
}

size_t ProcessList::size()
{
	return this->processes.size();
}

bool ProcessList::scanForProcesses()
{

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    PROCESSENTRY32 pe{};

    pe.dwSize = sizeof(PROCESSENTRY32);


    if (Process32First(hSnapshot, &pe))
    {
        do
        {
            Proc info;

            info.processID = pe.th32ProcessID;

            info.currentProcessName = pe.szExeFile;

            if (info.processID != 0 && info.processID != 4)
            {
                processes.push_back(info);
            }

        } while (Process32Next(hSnapshot, &pe));
    }

    CloseHandle(hSnapshot);

    return true;
}

