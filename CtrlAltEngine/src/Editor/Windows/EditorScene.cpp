#include "EditorScene.h"

namespace CtrlAltEditor
{

	EditorScene::EditorScene(Scene::SceneManager& _sceneManager, Debug::FrameTimer& _frameTimer) :
		sceneManager(_sceneManager),
		frameTimer(_frameTimer)
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


		}

		ImGui::End();
	}

	EditorScene::~EditorScene()
	{

	}
}


