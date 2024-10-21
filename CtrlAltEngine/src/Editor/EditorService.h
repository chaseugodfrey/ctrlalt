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

#include "EditorContext.h"
#include "Windows/EditorBaseWindow.h"
#include "../Debug/Debugger.h"

namespace CtrlAltEditor
{
	class EditorService
	{
	private:
		EditorContext& context;
		Debug::FrameTimer& frameTimer;

	public:

		EditorService(EditorContext&, Debug::FrameTimer&);

		void CreateEditorWindow(EditorWindowType);
		void AppSave() const;
		void AppQuit() const;

		std::string const ReadFPS() const;
	};
}

#endif