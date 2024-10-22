/******************************************************************************/
/*!
\group  	CtrlAlt
\file		EditorContext.h
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Sep 08, 2024
\brief

 */
 /******************************************************************************/

#ifndef EDITOR_CONTEXT_H
#define EDITOR_CONTEXT_H

#include "../ECS/ECS.h"
#include "../Scene/SceneManager.h"
#include "Windows/EditorBaseWindow.h"
#include <vector>
#include <memory>
#include "GLEW/GL/glew.h"

namespace CtrlAltEditor
{

	class EditorContext
	{
	private:
		Scene::SceneManager& sceneManager;

	public:

		// Constructor
		EditorContext(Scene::SceneManager&);
		~EditorContext();

		// Editor Variables
		std::vector<std::unique_ptr<EditorWindow>> windowList;

		bool isDirty;

		// Scene
		GLuint frameBufferID;

		std::weak_ptr<ECS::Entity> selectedObject;


		
	};
}

#endif


