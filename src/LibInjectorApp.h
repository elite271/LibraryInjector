#pragma once
#include <memory>
#include <optional>

#include "imgui.h"

#include "ProcessList.h"
#include "HandleWrapper.h"
#include "FileDialog.h"

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

	int selected_index = -1;

	std::unique_ptr<Proc> selectedProcess;
	std::optional<HandleWrapper> attachedProcess;
};
