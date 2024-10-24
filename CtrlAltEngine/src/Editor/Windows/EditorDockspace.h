/******************************************************************************/
/*!
\group  	CtrlAlt
\file		EditorDockspace.h
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Oct 20, 2024
\brief

 */
 /******************************************************************************/

#ifndef EDITOR_DOCKSPACE_H
#define EDITOR_DOCKSPACE_H

#include "EditorBaseWindow.h"

namespace CtrlAltEditor
{
	class EditorDockspace : public EditorWindow
	{

	public:

		explicit EditorDockspace(EditorService&, EditorContext const&);
		void Display() override;
		//friend void ConsoleLog(const std::string);

		~EditorDockspace();

	};
}

#endif