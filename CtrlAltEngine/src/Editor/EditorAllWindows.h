#ifndef EDITOR_ALL_WINDOWS_H
#define EDITOR_ALL_WINDOWS_H

#include "Windows/EditorBaseWindow.h"
#include "Windows/EditorMenuBar.h"
#include "Windows/EditorPlayBar.h"
#include "Windows/EditorDockspace.h"
#include "Windows/EditorScene.h"
#include "Windows/EditorHierarchy.h"
#include "Windows/EditorInspector.h"
#include "Windows/EditorConsole.h"

namespace CtrlAltEditor
{
	enum EditorWindowType
	{
		MENUBAR,
		PLAYBAR,
		DOCKSPACE,
		SCENE,
		HIERARCHY,
		INSPECTOR,
		CONSOLE,
		PERFORMANCE
	};
}

#endif // !EDITOR_ALL_WINDOWS_H


