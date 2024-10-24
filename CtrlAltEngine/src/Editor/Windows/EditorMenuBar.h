/******************************************************************************/
/*!
\group  	CtrlAlt
\file		EditorMenu.h
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Oct 20, 2024
\brief

 */
 /******************************************************************************/

#ifndef EDITOR_MENU_H
#define EDITOR_MENU_H

#include "EditorBaseWindow.h"

namespace CtrlAltEditor
{
	class EditorService;
	class EditorContext;

	class EditorMenuBar : public EditorWindow
	{

	public:

		explicit EditorMenuBar(EditorService&, EditorContext const&);
		void Display() override;

		~EditorMenuBar();
	};
}

#endif