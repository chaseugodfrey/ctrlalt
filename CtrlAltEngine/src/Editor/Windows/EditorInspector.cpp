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
	EditorInspector::EditorInspector(EditorService& _service, EditorContext const& _context) :
		EditorWindow(_service, _context),
		treeFlags(ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_AllowItemOverlap) {};

	void EditorInspector::Display()
	{
		if (ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoCollapse))
		{
			if (context.selectedEntity.size() > 0)
			{
				auto& entity = context.selectedEntity[0];
				if (entity.HasComponent<Component::CTransform>()) { DisplayTransform(entity); }

			}


		}
		ImGui::End();
	}

	EditorInspector::~EditorInspector() {};

	void EditorInspector::DisplayTransform(ECS::Entity const& entity)
	{
		auto& transform = entity.GetComponent<Component::CTransform>();
		if (ImGui::TreeNodeEx("Transform", treeFlags))
		{
			ImGui::SameLine();
			if (ImGui::Button("+"))
			{

			}

			ImGui::Spacing();

			// Translation
			ImGui::Text("Translation");
			ImGui::SameLine(150.0f);
			ImGui::SetNextItemWidth(100.0f);
			ImGui::DragFloat("x##t", &transform.position.x, 0.1f, 0.0f, 0.0f, "X: %.3f");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(100.0f);
			ImGui::DragFloat("y##t", &transform.position.y, 0.1f, 0.0f, 0.0f, "Y: %.3f");

			// Scale
			ImGui::Text("Scale");
			ImGui::SameLine(150.0f);
			ImGui::SetNextItemWidth(100.0f);
			ImGui::DragFloat("x##s", &transform.scale.x, 0.1f, 0.0f, 0.0f, "X: %.3f");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(100.0f);
			ImGui::DragFloat("y##s", &transform.scale.y, 0.1f, 0.0f, 0.0f, "Y: %.3f");

			// Rotation
			ImGui::Text("Rotation");
			ImGui::SameLine(150.0f);
			ImGui::SetNextItemWidth(100.0f);
			float rot = transform.rotation;
			ImGui::DragFloat("##r", &rot, 0.1f, 0.0f, 0.0f, "%.1f");
			transform.rotation = rot;

			ImGui::TreePop();

		}

	}
}