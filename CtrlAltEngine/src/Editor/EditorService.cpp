#include "EditorService.h"
#include "../Logger/Logger.h"

namespace CtrlAltEditor
{

	EditorService::EditorService(EditorContext& _context) : context(_context) {};

	void EditorService::CreateWindow(EditorWindowType window)
	{

	}

	void EditorService::AppSave()
	{
		Logger::LogInfo("Saved");
	}

	void EditorService::AppQuit()
	{
		AppSave();
		Logger::LogInfo("Quit");
	}
}