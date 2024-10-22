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
#include <vector>
#include <memory>

namespace CtrlAltEditor
{
	class EditorScene : public EditorWindow
	{
		Scene::SceneManager& sceneManager;
		Debug::FrameTimer& frameTimer;
	public:

		EditorScene(Scene::SceneManager&, Debug::FrameTimer&);
		void Display() override;
		~EditorScene();
	};
}

#endif