/******************************************************************************/
/*!
\group  	CtrlAlt
\file		EditorWindow.h
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Sep 08, 2024
\brief

 */
 /******************************************************************************/

#ifndef EDITOR_WINDOW_H
#define EDITOR_WINDOW_H

#include "Editor_Includes.h"
#include <string>

namespace Editor
{
	class EditorWindow
	{
	public:

		std::string label;

		virtual void Display() = 0;

		virtual ~EditorWindow() = default;
	};
}

#endif