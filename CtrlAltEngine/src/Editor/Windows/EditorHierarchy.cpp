#ifndef EDITOR_HIERARCHY_H
#define EDITOR_HIERARCHY_H

#include "EditorHierarchy.h"

namespace CtrlAltEditor
{
	void EditorHierarchy::Display()
	{
		if (ImGui::Begin("Hierarchy", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
		{
			static std::string test_text;
			ImGui::InputText("Test Text", &test_text);

		}

		ImGui::End();

	}
}

#endif