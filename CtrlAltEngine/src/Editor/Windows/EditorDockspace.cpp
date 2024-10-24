#include "EditorDockspace.h"

namespace CtrlAltEditor 
{
	EditorDockspace::EditorDockspace(EditorService& _service, EditorContext const& _context) :
		EditorWindow(_service, _context) {};

	void EditorDockspace::Display()
	{
		ImVec2 dockspace_size = ImVec2(1920.0f, 1000.0f);
		ImVec2 dockspace_pos = ImVec2(0.0f, 80.0f);

		ImGui::SetNextWindowPos(dockspace_pos);
		ImGui::SetNextWindowSize(dockspace_size);
		//ImGui::SetNextWindowViewport(main_viewport->ID);

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		//ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), 0, NULL);

		ImGui::Begin("Dockspace", NULL, ImGuiWindowFlags_NoTitleBar);
		ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
		ImGui::DockSpace(dockspace_id, dockspace_size, ImGuiDockNodeFlags_None);
		ImGui::End();	
	}

	EditorDockspace::~EditorDockspace() {};
}

