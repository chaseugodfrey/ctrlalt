#include "EditorService.h"
#include "EditorAllWindows.h"
#include "../Logger/Logger.h"

namespace CtrlAltEditor
{
	EditorService::EditorService(EditorContext& _context, Scene::SceneManager& _sceneManager, Debug::FrameTimer& _frameTimer): 
		context(_context), 
		sceneManager(_sceneManager), 
		frameTimer(_frameTimer) 
	{
		Initialize();
	};

	void EditorService::Initialize()
	{
		CreateEditorWindow<EditorMenuBar>();
		CreateEditorWindow<EditorPlayBar>();
		CreateEditorWindow<EditorScene>();
		CreateEditorWindow<EditorHierarchy>();
		CreateEditorWindow<EditorInspector>();
		CreateEditorWindow<EditorConsole>();
	}

	template <typename WindowType>
	void EditorService::CreateEditorWindow()
	{
		auto window = std::make_unique<WindowType>(*this, context);
		context.windowList.push_back(std::move(window));
	}

	//template <typename WindowType>
	//std::unique_ptr<EditorWindow> EditorWindowFactory<WindowType>::Create(EditorService& service)
	//{
	//	std::unique_ptr<EditorWindow> window;
	//	window = std::make_unique<WindowType>(service);

	//	//switch (type)
	//	//{
	//	//case CtrlAltEditor::MENUBAR:
	//	//	window = std::make_unique<EditorMenuBar>(*this);
	//	//	break;
	//	//case CtrlAltEditor::PLAYBAR:
	//	//	window = std::make_unique<EditorPlayBar>();
	//	//	break;
	//	//case CtrlAltEditor::SCENE:
	//	//	window = std::make_unique<EditorScene>(sceneManager, frameTimer, context.frameBufferID);
	//	//	break;
	//	//case CtrlAltEditor::HIERARCHY:
	//	//	window = std::make_unique<EditorHierarchy>(sceneManager);
	//	//	break;
	//	//case CtrlAltEditor::INSPECTOR:
	//	//	window = std::make_unique<EditorInspector>();
	//	//	break;
	//	//case CtrlAltEditor::CONSOLE:
	//	//	window = std::make_unique<EditorConsole>();
	//	//	break;
	//	//default:
	//	//	break;
	//	//}
	//	return window;
	//}

	void EditorService::CreateEntityInScene()
	{
		sceneManager.CreateEntityInScene();
		std::cout << "Created Entity" << std::endl;
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

	void EditorService::UpdateSelectedObject(ECS::Entity selected)
	{
		if (context.selectedEntity.size() > 0)
			context.selectedEntity.pop_back();
		context.selectedEntity.push_back(selected);
	}

	std::string const EditorService::ReadFPS() const
	{
		return frameTimer.ReadFPS();
	}

	Scene::SceneManager& EditorService::GetSceneManager()
	{
		return sceneManager;
	}

	Debug::FrameTimer& EditorService::GetFrameTimer()
	{
		return frameTimer;
	}

}