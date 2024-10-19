/******************************************************************************/
/*!
\group  	CtrlAlt
\file		EditorMenu.h
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Sep 08, 2024
\brief

 */
 /******************************************************************************/

#ifndef EDITOR_MENU_H
#define EDITOR_MENU_H

#include "EditorBaseWindow.h"

namespace CtrlAltEditor
{
	class EditorMenu : public EditorWindow
	{
	private:

	public:

		void Display() override;

		~EditorMenu();
	};
}

#endif