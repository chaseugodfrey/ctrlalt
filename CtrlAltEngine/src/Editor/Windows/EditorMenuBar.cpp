/******************************************************************************/
/*!
\group  	CtrlAlt
\file		EditorMenu.cpp
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Oct 20, 2024
\brief

 */
 /******************************************************************************/

#include "EditorMenuBar.h"

namespace CtrlAltEditor
{

	void EditorMenuBar::Display()
	{
		// Set Menu Bar Size & position
		// Remember to change size dynamically
		ImGui::SetNextWindowSize(ImVec2(1920, 40));
		ImGui::SetNextWindowPos(ImVec2(0, 0));

		static ImVec2 frame_padding(5.0f, 10.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, frame_padding);

		// Menu Bar Rendering
		if (ImGui::Begin("AxelUnderland", NULL,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking))
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::SetWindowFontScale(1.2f);
				// FILE DROP DOWN MENU
				if (ImGui::BeginMenu("File"))
				{
					// 
					if (ImGui::MenuItem("Exit"))
					{

					}

					// DISABLE SAVE SCENE FOR NOW
					//if (ImGui::MenuItem("Save Scene"))
					//{
					//	scene_manager->SaveScene();
					//}

					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Create"))
				{
					//ImGui::BeginDisabled();

					if (ImGui::MenuItem("Entity (WIP)"))
					{
						//scene_manager->CreateEntityInScene("Basic");
						//ECS::Entity entity = registry->CreateEntity();

					}
					//ImGui::EndDisabled();
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

		};

		ImGui::PopStyleVar();
		ImGui::End();

	}

	EditorMenuBar::~EditorMenuBar()
	{

	}
}
