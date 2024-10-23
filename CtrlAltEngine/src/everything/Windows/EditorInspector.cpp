/******************************************************************************/
/*!
\group  	CtrlAlt
\file		EditorInspector.cpp
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Oct 20, 2024
\brief

 */
 /******************************************************************************/
#include "../src/pch.h"
#include "EditorInspector.h"

/**
 * @brief Displays the inspector window in the editor.
 *
 * This function creates and renders the inspector window, allowing users to view
 * and edit entity properties such as "Transform". It includes drag-and-drop for
 * modifying position coordinates and an input text field for serialization testing.
 *
 * @return void This function does not return a value.
 */
namespace CtrlAltEditor
{
	void EditorInspector::Display()
	{
		//ImGui::SetNextWindowSize(ImVec2(400, 500));
		//ImGui::SetNextWindowPos(ImVec2(0, 40));

		if (ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoCollapse))
		{
			if (ImGui::TreeNode("Transform"))
			{
				static float coord[2]{ 0, 0 };
				ImGui::DragFloat2("x: ", coord);
				ImGui::TreePop();
			}

			//if (ImGui::InputText("Serialize Test", &test_text))
			//{

			//}

		}

		ImGui::End();
	}

	EditorInspector::~EditorInspector() {};
}