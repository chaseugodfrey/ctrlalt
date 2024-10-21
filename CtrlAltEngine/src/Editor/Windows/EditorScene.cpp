#include "EditorScene.h"

namespace CtrlAltEditor
{
	//ImGui::SetNextWindowSize(ImVec2(1120, 500));
	//ImGui::SetNextWindowPos(ImVec2(400, 40));

	/**
	 * @brief Displays scene window in the editor.
	 *
	 * This function displays the scene rendered as a frame buffer
	 * from the rendering system after converting it into an ImGUI
	 * texture.
	 *
	 * Not currently working now.
	 *
	 * @return void This function does not return a value.
	 */

	void EditorScene::Display()
	{
		if (ImGui::Begin("Scene", NULL))
		{


		}

		ImGui::End();
	}
}


