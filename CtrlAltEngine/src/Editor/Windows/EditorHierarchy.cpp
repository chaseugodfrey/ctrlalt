#include "EditorHierarchy.h"
#include "../EditorService.h"
#include "../../ECS/ECS.h"

namespace CtrlAltEditor
{
	EditorHierarchy::EditorHierarchy(EditorService& _service, EditorContext const& _context) : EditorWindow(_service, _context) {};

	void EditorHierarchy::Display()
	{
		if (ImGui::Begin("Hierarchy", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanFullWidth;

			static int selected_node = -1;
			int id = 0;

			for (auto& entity : service.GetSceneManager().GetEntityList())
			{
				std::string name = entity.GetComponent<Component::CIdentifier>().name;
				name += "##";
				name += id;

				ImGuiTreeNodeFlags node_flags = base_flags;

				int childCount = 0;

				if (childCount <= 0)
					node_flags |= ImGuiTreeNodeFlags_Leaf;

				if (selected_node == id)
					node_flags |= ImGuiTreeNodeFlags_Selected;

				if (ImGui::TreeNodeEx(name.c_str(), node_flags))
				{

					if (ImGui::IsItemClicked())
					{
						std::cout << "clicked" << std::endl;
						selected_node = id;
						service.UpdateSelectedObject(entity);
					}

					if (ImGui::BeginPopupContextItem())
					{
						if (ImGui::Selectable("Add Entity"));
						ImGui::SeparatorText("Components");
						if (ImGui::Selectable("Add Collider"));
						if (ImGui::Selectable("Add Rigidbody"));
						if (ImGui::Selectable("Add Animation"));

						ImGui::EndPopup();
					}
					//ImGui::Isitem

					ImGui::TreePop();
				};

				id++;
			} 
		}

		ImGui::End();

	}

	EditorHierarchy::~EditorHierarchy() {};
}