#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>

#include <vector>
#include <string>

#include "ProcInfo.h"

class ProcessList
{
public:
	ProcessList();
	~ProcessList();


	bool init();

	bool Refresh();

	void Clear();

	Proc at(size_t i);

	size_t size();

private:
	bool scanForProcesses();

	std::vector<Proc> processes;
};