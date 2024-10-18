#include <GLEW/GL/glew.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include "AppManager.h"
#include "Engine/Engine.h"
#include "Editor/Editor.h"

namespace 
{
    GLFWwindow* CreateGLFWwindow(int width, int height);
    void EnableMemoryLeakChecking(int breakAlloc = -1);
}

using namespace ApplicationManager;

namespace Application
{
	void App::Init()
	{
        if (!glfwInit()) {
            return;
        }

        isRunning = true;

        // CREATE WINDOWED APPLICATION
        glClearColor(1.f, 1.f, 0.f, 1.f);

        GLFWwindow* window = CreateGLFWwindow(1920, 1080);
        AppManager::GetInstance().Setup(window);
        AppManager::GetInstance().Init();
	}
	
	void App::Run()
	{

        EnableMemoryLeakChecking();
        while (isRunning && !glfwWindowShouldClose(AppManager::GetInstance().GetAppWindow()))
        {
            // SET BACKGROUND
            glfwMakeContextCurrent(AppManager::GetInstance().GetAppWindow());
            glClearColor(1.f, 1.f, 1.f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glfwSwapBuffers(AppManager::GetInstance().GetAppWindow());
            glfwPollEvents();

            AppManager::GetInstance().Run();
        }
	}
	
	void App::Shutdown()
	{
        AppManager::GetInstance().Shutdown();

        glfwDestroyWindow(AppManager::GetInstance().GetAppWindow());
        glfwTerminate();
	}
}

// HELPER FUNCTIONS

namespace {

    GLFWwindow* CreateGLFWwindow(int width, int height)
    {

        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
        glfwWindowHint(GLFW_DEPTH_BITS, 24);
        glfwWindowHint(GLFW_RED_BITS, 8); glfwWindowHint(GLFW_GREEN_BITS, 8);
        glfwWindowHint(GLFW_BLUE_BITS, 8); glfwWindowHint(GLFW_ALPHA_BITS, 8);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        width = mode->width;
        height = mode->height;

        GLFWwindow* window = glfwCreateWindow(width, height, "AxelUnderland", NULL, nullptr);
        if (!window) {

            glfwTerminate();
            return window;
        }

        glfwMakeContextCurrent(window);

        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* /*window*/, int width, int height) {
            glViewport(0, 0, width, height);
            });

        return window;
    }

    void EnableMemoryLeakChecking(int breakAlloc)
    {
        //Set the leak checking flag
        int tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
        tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;
        _CrtSetDbgFlag(tmpDbgFlag);

        //If a valid break alloc provided set the breakAlloc
        if (breakAlloc != -1) _CrtSetBreakAlloc(breakAlloc);
    }

}
 
