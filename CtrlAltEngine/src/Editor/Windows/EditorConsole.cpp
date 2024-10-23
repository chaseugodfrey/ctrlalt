/******************************************************************************/
/*!
\group  	CtrlAlt
\file		EditorConsole.cpp
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Oct 20, 2024
\brief

 */
 /******************************************************************************/

#include "EditorConsole.h"

namespace CtrlAltEditor
{
	EditorConsole::EditorConsole(EditorService& _service, EditorContext const& _context) : EditorWindow(_service, _context) {};

	void EditorConsole::Display()

	{
		//ImGui::SetNextWindowSize(ImVec2(800, 500));
		//ImGui::SetNextWindowPos(ImVec2(400, 500));


		if (ImGui::Begin("Console", NULL, ImGuiWindowFlags_NoCollapse))
		{

			if (ImGui::Button("Clear"))
			{
				ClearConsole();
			}

			static bool auto_scroll = true;
			static float scroll_pos = 0.f;

			if (ImGui::BeginTable("Console_Table", 1, ImGuiTableFlags_Borders | ImGuiTableFlags_BordersInner | ImGuiTableRowFlags_Headers | ImGuiTableFlags_ScrollY))
			{

				for (size_t i = 0; i < logList.size(); i++)
				{
					ImGui::TableNextRow(NULL, 25.0f);
					ImGui::TableNextColumn();
					ImGui::Text(logList[i].c_str());
				}

				if (auto_scroll)
					ImGui::SetScrollY(ImGui::GetScrollMaxY());

				if (ImGui::GetScrollY() < ImGui::GetScrollMaxY() - 10.0f)
					auto_scroll = false;
				else
					auto_scroll = true;



				ImGui::EndTable();
			}

		}

		ImGui::End();
	}

	/**
	 * @brief Clears the console log.
	 *
	 * This function clears all the text currently stored in the console's log.
	 *
	 * @return void This function does not return a value.
	 */

	void EditorConsole::ClearConsole()
	{
		logList.clear();
	}

	EditorConsole::~EditorConsole() {}
}
