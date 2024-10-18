#ifndef APP_MANAGER_H
#define APP_MANAGER_H

#include "GLEW/GL/glew.h"
#include "GLFW/glfw3.h"
#include "../Engine/Engine.h"
#include "../Editor/Editor.h"

namespace ApplicationManager
{
    class AppManager
    {
    private:

        std::unique_ptr<Engine::Engine> m_engine;
        std::unique_ptr<Editor::Editor> m_editor;
        std::unique_ptr<GLFWwindow*> m_window;

        AppManager();

    public:

        Engine::Engine* GetEngine();
        Editor::Editor* GetEditor();
        GLFWwindow* GetAppWindow();

        ~AppManager();
        AppManager(const AppManager& obj) = delete;
        AppManager& operator=(AppManager&) = delete;

        static AppManager& GetInstance();

        void Init(GLFWwindow*);
        void Run();
        void Shutdown();
    };
}

#endif