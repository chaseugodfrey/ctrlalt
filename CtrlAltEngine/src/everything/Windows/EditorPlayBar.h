/******************************************************************************/
/*!
\group  	CtrlAlt
\file		EditorPlayBar.h
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Sep 08, 2024
\brief

 */
 /******************************************************************************/

#ifndef EDITOR_PLAY_H
#define EDITOR_PLAY_H

#include "EditorBaseWindow.h"
#include <vector>
#include <memory>

namespace CtrlAltEditor
{

	class EditorPlayBar : public EditorWindow
	{
	public:

		void Display() override;

		~EditorPlayBar();
	};
}

#endif