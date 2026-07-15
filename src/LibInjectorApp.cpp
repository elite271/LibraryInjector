#include "LibInjectorApp.h"
#include <iostream>
#include <format>

LibInjectorApp::LibInjectorApp()
{
}

LibInjectorApp::~LibInjectorApp()
{
}

bool LibInjectorApp::Init()
{
	if (!list.init())
	{
		std::cerr << "Process List init failed" << std::endl;
		return false;
	}

	if (!fileDialog.Init())
	{
		std::cerr << "File Dialog init failed" << std::endl;
		return false;
	}

	return true;
}

void LibInjectorApp::Render()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(io.DisplaySize);

	ImGui::Begin("Library Injector", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);

	ImGui::BeginChild("ProcList", ImVec2(300, 0), true);

	if (ImGui::Button("Refresh"))
	{
		RefreshButtonPressed();
		attachedProcess.reset();
	}

	// float listbox_height = ImGui::GetContentRegionAvail().y - 30.0f;
	// if (ImGui::BeginListBox("##Processes", ImVec2(-FLT_MIN, listbox_height)))
	if (ImGui::BeginListBox("##Processes", ImVec2(-FLT_MIN, -FLT_MIN)))
	{
		for (auto i = 0u; i < list.size(); ++i)
		{
			const bool is_selected = (selected_index == i);

			std::string label = list.at(i).currentProcessName + "##" + std::to_string(list.at(i).processID);
			if (ImGui::Selectable(label.c_str(), is_selected))
			{
				selected_index = i;

				OnListSelect();
			}

			if (is_selected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndListBox();
	}

	ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild("InjectorControls", ImVec2(0, 0), true);

	if (ImGui::Button("Open"))
	{
		fileDialog.Show();
	}
	ImGui::Text("Selected file: %ls", fileDialog.GetSelectedPath().c_str());

	if (selectedProcess)
	{
		ImGui::Text("Selected Process: %s", selectedProcess->currentProcessName.c_str());
	}
	else
	{
		ImGui::TextDisabled("No Process");
	}

	bool CanInject = attachedProcess.has_value() && !fileDialog.GetSelectedPath().empty();

	ImGui::BeginDisabled(!CanInject);

	if (ImGui::Button("Inject"))
	{
		HANDLE handle = this->attachedProcess->GetHandle();
		
		injector.InjectDLL(handle, fileDialog.GetSelectedPath().c_str());
	}

	ImGui::EndDisabled();

	ImGui::EndChild();

	ImGui::End();
}

void LibInjectorApp::OnListSelect()
{
	this->selectedProcess = std::make_unique<Proc>(list.at(selected_index));

	if (selectedProcess)
	{
		attachedProcess.emplace(*selectedProcess);
	}
}

bool LibInjectorApp::RefreshButtonPressed()
{
	selected_index = -1;

	selectedProcess.reset();

	return list.Refresh();
}
