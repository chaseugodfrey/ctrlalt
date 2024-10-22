#include "EditorScene.h"

namespace CtrlAltEditor
{

	EditorScene::EditorScene(Scene::SceneManager const& _sceneManager, Debug::FrameTimer const& _frameTimer, GLuint id) :
		sceneManager(_sceneManager),
		frameTimer(_frameTimer),
		frameBufferID(id)
	{};

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
			const float scene_width		= ImGui::GetContentRegionAvail().x;
			const float scene_height	= ImGui::GetContentRegionAvail().y;

			ImVec2 pos = ImGui::GetCursorScreenPos();

			ImGui::GetWindowDrawList()->AddImage(
				(void*)frameBufferID,
				pos,
				ImVec2(pos.x + scene_width, pos.y + scene_height),
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


