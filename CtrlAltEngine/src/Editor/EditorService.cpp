#include "EditorService.h"
#include "EditorAllWindows.h"
#include "../Logger/Logger.h"

namespace CtrlAltEditor
{
	EditorService::EditorService(EditorContext& _context, Scene::SceneManager& _sceneManager, Debug::FrameTimer& _frameTimer): 
		context(_context), 
		sceneManager(_sceneManager), 
		frameTimer(_frameTimer) {};

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
			window = std::make_unique<EditorScene>(sceneManager, frameTimer);
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

	void EditorService::CreateEntity() const
	{
		
	}

	std::string const EditorService::ReadFPS() const
	{
		return frameTimer.ReadFPS();
	}
}