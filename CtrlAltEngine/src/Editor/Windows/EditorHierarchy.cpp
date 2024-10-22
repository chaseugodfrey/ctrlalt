#include "EditorHierarchy.h"
#include "../../ECS/ECS.h"

namespace CtrlAltEditor
{
	EditorHierarchy::EditorHierarchy(Scene::SceneManager& _sceneManager) :
		sceneManager(_sceneManager) {};

	void EditorHierarchy::Display()
	{
		if (ImGui::Begin("Hierarchy", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
		{
			for (auto& entity : sceneManager.GetScene()->GetEntities())
			{
				//std::string name = entity.GetComponent<Component::CIdentifier>().name;
				//ImGui::Text(name.c_str());
			} 

		}

		ImGui::End();

	}

	EditorHierarchy::~EditorHierarchy() {};
}