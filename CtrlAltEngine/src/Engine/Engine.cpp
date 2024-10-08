/** 
@group CTRL ALT
@file Engine.cpp
@brief Implementation of the Engine class
Created by Chase Rodrigues
rodrigues.i@digipen.edu
*/ 


// INCLUDES
// =========================================================================================================
#include "Engine.h"
#include <iostream>
#include "glm/glm.hpp"
#include "../Render/Render.h"
#include "../Components/CTransform.h"
#include "../Components/CRigidBody.h"
#include "../Components/CCollider.h"
#include "../Systems/SMovement.h"
#include "../Systems/SPhysics.h"
#include "../Systems/SKeyboardControl.h"
#include "../Systems/SCollision.h"
#include "../Math/MathLib.h"
#include "../Scene/Scene.h"
#include "../Debug/Debugger.h"


using namespace MathLib;

// DEFINITIONS
// =========================================================================================================

// STORE GLOBALS IN BETTER PLACE AFTER M1

//Render::RenderPipeline renderSystem;
Input::Input_Container global_input;// definition of the global variable 
Scene::Scene* sceneSystem;
Debug::FrameTimer* frameTimer; //Defining frameTimer for fps

namespace {

    GLFWwindow* CreateGLFWwindow(int width, int height);
}

GLFWwindow* main_window;
namespace Engine{

    void EnableMemoryLeakChecking(int breakAlloc = -1)
    {
        //Set the leak checking flag
        int tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
        tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;
        _CrtSetDbgFlag(tmpDbgFlag);

        //If a valid break alloc provided set the breakAlloc
        if (breakAlloc != -1) _CrtSetBreakAlloc(breakAlloc);
    }

    /// <summary>
    /// 
    /// </summary>
    Engine::Engine() : eventBus(std::make_unique<Event::EventBus>()), registry(std::make_unique<ECS::Registry>()), windowWidth(0), windowHeight(0), isRunning(false) {
        main_window = (nullptr);
        Logger::LogInfo("Engine Created");
    }

    /// <summary>
    /// 
    /// </summary>
    Engine::~Engine() {

        //Logger::LogInfo("Engine Deleted");
    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Initialize() {
        if (!glfwInit()) {
            return;
        }

        // CREATE WINDOWED APPLICATION
        glClearColor(1.f, 1.f, 0.f, 1.f);
        main_window = CreateGLFWwindow(windowWidth, windowHeight);


        //## initialise input systems,
        // key binds WASD, 1 rot, 2 scale.
        //## my input system will be a static variable in header.
        global_input.Init_System(main_window); 

        isRunning = true;
        sceneManager = std::make_unique<Scene::SceneManager>(registry.get());

		
        editor = new Editor::Editor();
        editor->Initialize(main_window, sceneManager.get(),&frameTimer);

        sceneManager->AddScene("Scene1", "Assets/scene1.txt");
        sceneManager->AddScene("Scene2", "Assets/scene2.txt");
        sceneManager->AddScene("Scene3", "Assets/scene3.txt");
        sceneManager->SwitchScene("Scene1");

    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::ProcessInput() {
        for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key) {
            int state = glfwGetKey(main_window, key);
            if (state == GLFW_PRESS) {
                eventBus->EmitEvent<KeyPressEvent>(key);
            }
        }
        if (glfwGetKey(main_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            isRunning = false;
        }
        global_input.Update(main_window); // able to dynamically change windows for keychecks
    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Setup() {
        // System Set Ups
		registry->AddSystem<System::SMovement>();
        registry->AddSystem<System::SPhysics>();
        registry->AddSystem<System::SAnimator>();
        registry->AddSystem<System::SRender>();
        registry->AddSystem<System::SCollision>();
        registry->AddSystem<System::SKeyboardControl>();
    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Update() {

        sceneManager->UpdateScene();

        eventBus->Reset();
		registry->GetSystem<System::SMovement>().Update();
        registry->GetSystem<System::SPhysics>().Update();
        registry->GetSystem<System::SCollision>().Update();
        registry->GetSystem<System::SKeyboardControl>().SubscribeToEvents(eventBus);
        registry->GetSystem<System::SAnimator>().Update(static_cast<GLfloat>(frameTimer.Get_dt()));
        registry->GetSystem<System::SRender>().UpdateFlags();
        global_input.Test_Left_Mouse_Button(frameTimer.Get_dt());
        global_input.Test_Keybinds();
        
        registry->Update();
        CheckGLError();
        editor->Update();

        frameTimer.update();
        if(frameTimer.GetFrameCount() == 59)
            std::cout << frameTimer.ReadFPS() << std::endl; //This is what's suppose to be on Editor huhu
        
        //sceneManager->UpdateScene();
    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Render() {

        // SET BACKGROUND
        glfwMakeContextCurrent(main_window);
        glClearColor(1.f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        editor->Draw();

        glfwSwapBuffers(main_window);
        glfwPollEvents();

        registry->GetSystem<System::SRender>().Render();

    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Run() {
        EnableMemoryLeakChecking();
        Setup();
        while (isRunning && !glfwWindowShouldClose(main_window) && !editor->GetExitPrompt()) {
			//Frame Timer
            frameTimer.update();
			
            //Keyboard Input
            glfwPollEvents();
            
			//Engine Update
            ProcessInput();
            Update();
            Render();
        }

        CheckGLError();
    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Destroy() {
        //   CheckGLError();
        registry->GetSystem<System::SRender>().Destroy();
        glfwDestroyWindow(main_window);
        editor->Destroy();
        glfwTerminate();
        if (editor)
            delete editor;
     //   CheckGLError();
    }

   

}
namespace {
    // HELPER FUNCTIONS
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
}