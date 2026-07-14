#pragma once
#include <memory>

#include "imgui.h"

#include "ProcessList.h"
#include "HandleWrapper.h"

class LibInjectorApp
{
public:
	 LibInjectorApp();
	~LibInjectorApp();

	bool Init();
	void Render();
	void OnListSelect();

private:
	ProcessList list{};

	int selected_index = -1;

	std::unique_ptr<Proc> selectedProcess;
	std::unique_ptr<HandleWrapper> attachedProcess;
};
