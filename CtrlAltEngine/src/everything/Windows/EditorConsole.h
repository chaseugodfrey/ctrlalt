/******************************************************************************/
/*!
\group  	CtrlAlt
\file		EditorConsole.h
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Oct 20, 2024
\brief

 */
 /******************************************************************************/

#ifndef EDITOR_CONSOLE_H
#define EDITOR_CONSOLE_H

#include "EditorBaseWindow.h"
#include <vector>

namespace CtrlAltEditor
{
	class EditorConsole : public EditorWindow
	{

	public:

		void Display() override;
		//friend void ConsoleLog(const std::string);

		~EditorConsole();

	private:

		std::vector<std::string> logList;

		void ClearConsole();

	};
}

#endif