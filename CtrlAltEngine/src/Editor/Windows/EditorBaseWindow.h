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

	class EditorService;
	class EditorContext;

	class EditorWindow
	{

	protected:
		EditorService& service;
		EditorContext const& context;
		
	public:

		std::string label;
		
		explicit EditorWindow(EditorService&, EditorContext const&);
		virtual void Display() = 0;
		virtual ~EditorWindow() = default;
	};
}

#endif