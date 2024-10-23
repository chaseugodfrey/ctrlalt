/******************************************************************************/
/*!
\group  	CtrlAlt
\file		EditorScene.h
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Sep 08, 2024
\brief

 */
 /******************************************************************************/

#ifndef EDITOR_SCENE_H
#define EDITOR_SCENE_H

#include "EditorBaseWindow.h"
#include "../../Scene/SceneManager.h"
#include "../../Debug/Debugger.h"
#include "GLEW/GL/glew.h"
#include <vector>
#include <memory>

namespace CtrlAltEditor
{
	class EditorScene : public EditorWindow
	{
		GLuint frameBufferID;

		Scene::SceneManager const& sceneManager;
		Debug::FrameTimer const& frameTimer;
	public:

		EditorScene(Scene::SceneManager const&, Debug::FrameTimer const&, GLuint);
		void Display() override;
		~EditorScene();
	};
}

#endif