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

#include "EditorInspector.h"
#include "../EditorService.h"
#include "../EditorContext.h"
#include "../../ECS/ECS.h"

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
	EditorInspector::EditorInspector(EditorService& _service, EditorContext const& _context) : EditorWindow(_service, _context) {};

	void EditorInspector::Display()
	{
		//ImGui::SetNextWindowSize(ImVec2(400, 500));
		//ImGui::SetNextWindowPos(ImVec2(0, 40));

		if (ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoCollapse))
		{
			if (context.selectedEntity.size() > 0)
			{
				auto& entity = context.selectedEntity[0];
				if (entity.HasComponent<Component::CTransform>())
				{
					std::cout << "has" << std::endl;
					auto& transform = entity.GetComponent<Component::CTransform>();
					if (ImGui::TreeNode("Transform"))
					{
						ImGui::DragFloat2("x: ", transform.position.elements);
						ImGui::TreePop();
					}
				}

				//if (ImGui::TreeNode("Transform"))
				//{
				//	static float coord[2]{ 0, 0 };
				//	ImGui::DragFloat2("x: ", coord);
				//	ImGui::TreePop();
				//}

				//if (ImGui::InputText("Serialize Test", &test_text))
				//{

				//}

			}


		}
		ImGui::End();
	}

	EditorInspector::~EditorInspector() {};
}