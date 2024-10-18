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
#include "../Application/AppManager.h"
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

Input::Input_Container global_input;// definition of the global variable 
Scene::Scene* sceneSystem;
Debug::FrameTimer* frameTimer; //Defining frameTimer for fps

using namespace ApplicationManager;

namespace Engine{


    /// <summary>
    /// 
    /// </summary>
    Engine::Engine() : eventBus(std::make_unique<Event::EventBus>()), registry(std::make_unique<ECS::Registry>()) {
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

        Setup();

        //## initialise input systems,
        // key binds WASD, 1 rot, 2 scale.
        //## my input system will be a static variable in header.
        global_input.Init_System(AppManager::GetInstance().GetAppWindow()); 

        sceneManager = std::make_unique<Scene::SceneManager>(registry.get());

        sceneManager->AddScene("Scene1", "Assets/scene1.txt");
        sceneManager->AddScene("Scene2", "Assets/scene2.txt");
        sceneManager->AddScene("Scene3", "Assets/scene3.txt");
        sceneManager->SwitchScene("Scene1");

    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::ProcessInput() {
        //for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key) {
        //    int state = glfwGetKey(main_window, key);
        //    if (state == GLFW_PRESS) {
        //        eventBus->EmitEvent<KeyPressEvent>(key);
        //    }
        //}
        //if (glfwGetKey(main_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        //    isRunning = false;
        //}
        global_input.Update(AppManager::GetInstance().GetAppWindow()); // able to dynamically change windows for keychecks
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
        glfwMakeContextCurrent(AppManager::GetInstance().GetAppWindow());
        glClearColor(1.f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(AppManager::GetInstance().GetAppWindow());
        glfwPollEvents();

        registry->GetSystem<System::SRender>().Render();

    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Run() {
        //Frame Timer
        frameTimer.update();

        //Engine Update
        ProcessInput();
        Update();
        Render();

        CheckGLError();
    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Destroy() {
        //   CheckGLError();
        registry->GetSystem<System::SRender>().Destroy();

     //   CheckGLError();
    }

  
}
