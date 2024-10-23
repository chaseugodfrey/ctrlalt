#include "EditorScene.h"
#include "../EditorContext.h"

namespace CtrlAltEditor
{
	EditorScene::EditorScene(EditorService& _service, EditorContext const& _context) : EditorWindow(_service, _context) {};

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
			// Resize texture according to window size
			const float scene_width	= ImGui::GetContentRegionAvail().x;
			const float scene_height = ImGui::GetContentRegionAvail().y;
			
			// hardcoded for now, retreive from window
			const float src_width = 1920.0f;
			const float src_height = 1080.0f;

			float scale_x = scene_width / src_width;
			float scale_y = scene_height / src_height;

			float scale = std::min(scale_x, scale_y);

			float display_width = src_width * scale;
			float display_height = src_height * scale;

			ImVec2 pos = ImGui::GetCursorScreenPos();
			float offset_x = (scene_width - display_width) * 0.5f;
			float offset_y = (scene_height - display_height) * 0.5f;

			pos.x += offset_x;
			pos.y += offset_y;

			ImGui::GetWindowDrawList()->AddImage(
				(void*)context.frameBufferID,
				pos,
				ImVec2(pos.x + display_width, pos.y + display_height),
				ImVec2(0, 1),
				ImVec2(1, 0)
			);

		}

		ImGui::End();
	}

	EditorScene::~EditorScene()
	{

	}
}


