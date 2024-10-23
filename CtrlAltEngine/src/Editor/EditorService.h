/******************************************************************************/
/*!
\group  	CtrlAlt
\file		EditorService.h
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Sep 08, 2024
\brief

 */
 /******************************************************************************/

#ifndef EDITOR_SERVICE_H
#define EDITOR_SERVICE_H

#include "EditorContext.h"
#include "Windows/EditorBaseWindow.h"
#include "../Scene/SceneManager.h"
#include "../Debug/Debugger.h"

namespace CtrlAltEditor
{
	class EditorService
	{
	private:
		EditorContext& context;
		Scene::SceneManager& sceneManager;
		Debug::FrameTimer& frameTimer;

	public:

		EditorService(EditorContext&, Scene::SceneManager&, Debug::FrameTimer&);

		// Windows
		void CreateEditorWindow(EditorWindowType);

		// Editor App
		void AppSave() const;
		void AppQuit() const;

		// Create
		void CreateEntity() const;

		std::string const ReadFPS() const;
	};
}

#endif