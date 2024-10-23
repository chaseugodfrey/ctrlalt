#include "../src/pch.h"
#include "EditorPlayBar.h"

namespace CtrlAltEditor
{

	/**
	 * @brief Displays the play state window in the editor.
	 *
	 * This function sets up and renders the play state window, which includes buttons
	 * for "Play" and "Stop", as well as displaying the current frames per second (FPS).
	 *
	 * @return void This function does not return a value.
	 */

	void EditorPlayBar::Display()
	{

		ImGui::SetNextWindowSize(ImVec2(1920, 40));
		ImGui::SetNextWindowPos(ImVec2(0, 40));

		if (ImGui::Begin("PlayState", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar))
		{

			ImVec2 btn_size(36, 20);
			ImGui::SameLine(ImGui::GetWindowWidth() * 0.5f);
			ImGui::Button("Play", btn_size); ImGui::SameLine();
			ImGui::Dummy(btn_size); ImGui::SameLine();
			ImGui::Button("Stop", btn_size);
		}

		ImGui::SameLine(ImGui::GetWindowWidth() * 0.95f);
		ImGui::Text("60");


		ImGui::End();
	}

	EditorPlayBar::~EditorPlayBar() 
	{
	
	};
}