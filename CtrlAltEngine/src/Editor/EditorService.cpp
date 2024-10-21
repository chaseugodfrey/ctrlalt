#include "EditorService.h"
#include "EditorAllWindows.h"
#include "../Logger/Logger.h"

namespace CtrlAltEditor
{
	EditorService::EditorService(EditorContext& _context, Debug::FrameTimer& _frameTimer) : context(_context), frameTimer(_frameTimer) {};

	void EditorService::CreateEditorWindow(EditorWindowType type)
	{
		std::unique_ptr<EditorWindow> window;

		switch (type)
		{
		case CtrlAltEditor::MENUBAR:
			window = std::make_unique<EditorMenuBar>();
			break;
		case CtrlAltEditor::PLAYBAR:
			window = std::make_unique<EditorPlayBar>();
			break;
		case CtrlAltEditor::SCENE:
			window = std::make_unique<EditorScene>();
			break;
		case CtrlAltEditor::HIERARCHY:
			window = std::make_unique<EditorHierarchy>();
			break;
		case CtrlAltEditor::INSPECTOR:
			window = std::make_unique<EditorInspector>();
			break;
		case CtrlAltEditor::CONSOLE:
			window = std::make_unique<EditorConsole>();
			break;
		default:
			break;
		}

		context.windowList.push_back(std::move(window));

	}

	void EditorService::AppSave() const
	{
		Logger::LogInfo("Saved");
	}

	void EditorService::AppQuit() const
	{
		AppSave();
		Logger::LogInfo("Quit");
	}

	std::string const EditorService::ReadFPS() const
	{
		return frameTimer.ReadFPS();
	}
}