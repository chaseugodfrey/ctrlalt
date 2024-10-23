/******************************************************************************/
/*!
\group  	CtrlAlt
\file		EditorHierarchy.h
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Sep 08, 2024
\brief

Defines 


Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef EDITOR_HIERACHY_H
#define EDITOR_HIERACHY_H

#include "EditorBaseWindow.h"

namespace CtrlAltEditor
{

	class EditorHierarchy : public EditorWindow
	{

	public:

		explicit EditorHierarchy(EditorService&, EditorContext const&);
		void Display() override;
		~EditorHierarchy();
	};

}

#endif // !EDITOR_HIERACHY_H