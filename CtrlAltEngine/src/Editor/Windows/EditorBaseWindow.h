/******************************************************************************/
/*!
\group  	CtrlAlt
\file		EditorWindow.h
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Oct 20, 2024
\brief

 */
 /******************************************************************************/

#ifndef EDITOR_WINDOW_H
#define EDITOR_WINDOW_H

#include <string>
#include "../EditorIncludes.h"

namespace CtrlAltEditor
{

	enum EditorWindowType
	{
		MENUBAR,
		PLAYBAR,
		SCENE,
		HIERARCHY,
		INSPECTOR,
		CONSOLE,
		PERFORMANCE
	};

	class EditorWindow
	{
	public:

		std::string label;
		
		virtual void Display() = 0;
		virtual ~EditorWindow() = default;
	};
}

#endif