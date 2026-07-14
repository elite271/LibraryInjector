#include "LibInjectorApp.h"

LibInjectorApp::LibInjectorApp()
{
}

LibInjectorApp::~LibInjectorApp()
{
}

bool LibInjectorApp::Init()
{
	return true;
}

void LibInjectorApp::Render()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(io.DisplaySize);

	ImGui::Begin("Hello, world!", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImGui::Text("Test");
	ImGui::End();
}
