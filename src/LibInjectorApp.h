#pragma once
#include <memory>
#include <optional>

#include "imgui.h"

#include "ProcessList.h"
#include "HandleWrapper.h"
#include "FileDialog.h"
#include "Injector.h"

class LibInjectorApp
{
public:
	 LibInjectorApp();
	~LibInjectorApp();

	bool Init();
	void Render();
	void OnListSelect();
	bool RefreshButtonPressed();

private:
	ProcessList list{};
	FileDialog fileDialog{};
	Injector injector{};

	int selected_index = -1;

	std::unique_ptr<Proc> selectedProcess;
	std::optional<HandleWrapper> attachedProcess;
};
