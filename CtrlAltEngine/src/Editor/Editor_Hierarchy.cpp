#include "Editor_Hierarchy.h"

namespace GameEditor
{
	void Hierarchy::Display()
	{
		if (ImGui::Begin("Hierarchy", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
		{
			static std::string test_text;
			ImGui::InputText("Test Text", &test_text);

		}

		ImGui::End();

	}
}