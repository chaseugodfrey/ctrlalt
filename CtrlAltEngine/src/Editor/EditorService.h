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
#include "../Scene/SceneManager.h"
#include "../Debug/Debugger.h"

namespace CtrlAltEditor
{
	enum EditorWindowType : int;

	class EditorService
	{
	private:
		EditorContext& context;
		Scene::SceneManager& sceneManager;
		Debug::FrameTimer& frameTimer;

		void Initialize();

	public:

		EditorService(EditorContext&, Scene::SceneManager&, Debug::FrameTimer&);

		// References
		Scene::SceneManager& GetSceneManager();
		Debug::FrameTimer& GetFrameTimer();

		// Windows
		template <typename WindowType>
		void CreateEditorWindow();
		void CreateEntityInScene();

		// Editor App
		void AppSave() const;
		void AppQuit() const;

		// Create
		void CreateEntity() const;

		// Scene Control
		void UpdateSelectedObject(ECS::Entity);

		std::string const ReadFPS() const;
	};

}

#endif