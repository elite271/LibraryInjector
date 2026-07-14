#include "LibInjectorApp.h"
#include <iostream>

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

	return true;
}

void LibInjectorApp::Render()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(io.DisplaySize);

	ImGui::Begin("Library Injector", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);


	// float listbox_height = ImGui::GetContentRegionAvail().y - 30.0f;
	// if (ImGui::BeginListBox("##Processes", ImVec2(-FLT_MIN, listbox_height)))
	if (ImGui::BeginListBox("##Processes"))
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

			// Set the initial focus when opening the combo (scrolling to the item)
			if (is_selected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndListBox();
	}




	ImGui::End();
}

void LibInjectorApp::OnListSelect()
{
	this->selectedProcess = std::make_unique<Proc>(list.at(selected_index));
}
