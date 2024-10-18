#include "AppManager.h"

namespace ApplicationManager
{

    // GLOBAL ACCESSORS

    AppManager& AppManager::GetInstance()
    {
        static AppManager m_app_manager;
        return m_app_manager;
    }

    // CLASS MEMBER ACCESSORS

    Engine::Engine* AppManager::GetEngine()
    {
        return m_engine.get();
    }

    Editor::Editor* AppManager::GetEditor()
    {
        return m_editor.get();
    }

    GLFWwindow* AppManager::GetAppWindow()
    {
        return *(m_window.get());
    }

    AppManager::AppManager() :
        m_engine(nullptr),
        m_editor(nullptr),
        m_window(nullptr)
    {}

    AppManager::~AppManager() {}

    void AppManager::Setup(GLFWwindow* window)
    {
        m_engine = std::make_unique<Engine::Engine>();
        m_editor = std::make_unique<Editor::Editor>();
        m_window = std::make_unique<GLFWwindow*>(window);
    }

    void AppManager::Init()
    {
        m_engine->Initialize();
        m_editor->Initialize();
    }

    void AppManager::Run()
    {
        m_engine->Run();
        m_editor->Update();
    }

    void AppManager::Shutdown()
    {
        m_engine->Destroy();
        m_editor->Destroy();
    }
}
