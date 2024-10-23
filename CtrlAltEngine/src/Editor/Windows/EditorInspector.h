/******************************************************************************/
/*!
\group  	CtrlAlt
\file		EditorInspector.h
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Oct 20, 2024
\brief

 */
 /******************************************************************************/

#ifndef EDITOR_INSPECTOR_H
#define EDITOR_INSPECTOR_H

#include "EditorBaseWindow.h"
#include <vector>

namespace CtrlAltEditor
{
	class EditorInspector : public EditorWindow
	{

	public:

		explicit EditorInspector(EditorService&, EditorContext const&);
		void Display() override;

		~EditorInspector();

	private:

	};
}

#endif