/******************************************************************************/
/*!
\group  	CtrlAlt
\file		EditorService.h
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Sep 08, 2024
\brief

 */
 /******************************************************************************/

#ifndef EDITOR_SERVICE_H
#define EDITOR_SERVICE_H

#include "EditorService.h"
#include "EditorContext.h"
#include "Windows/EditorBaseWindow.h"

namespace CtrlAltEditor
{
	class EditorService
	{
	private:
		EditorContext& context;

	public:

		EditorService(EditorContext&) noexcept;

		void CreateWindow(EditorWindowType);
		void AppSave();
		void AppQuit();
	};
}

#endif