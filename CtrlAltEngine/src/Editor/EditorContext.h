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
#include <vector>
#include <memory>

namespace CtrlAltEditor
{
	class EditorWindow;

	class EditorContext
	{
	public:
		std::vector<std::unique_ptr<EditorWindow>> windowList;

		bool isDirty;

		std::weak_ptr<ECS::Entity> selectedObject;
		
	};
}

#endif