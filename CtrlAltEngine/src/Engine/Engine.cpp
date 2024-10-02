/** 
@group CTRL ALT
@file Engine.cpp
@brief Implementation of the Game class
Created by Michael Lazaroo
m.lazaroo@digipen.edu
*/ 


// INCLUDES
// =========================================================================================================
#include "Engine.h"
#include <iostream>
#include "glm/glm.hpp"
#include "../Components/CTransform.h"
#include "../Components/CRigidBody.h"
#include "../Systems/SMovement.h"
#include "../Systems/SPhysics.h"
#include "../Math/MathLib.h"
#include "../Systems/SKeyboardControl.h"
#include "../Scene/Scene.h"
#include "../Debug/Debugger.h"

#include "../Render/Render.h"

using namespace MathLib;

// DEFINITIONS
// =========================================================================================================

//Render::RenderPipeline renderSystem;
Input::Input_Container global_input;// definition of the global variable 
//Render::RenderPipeline renderSystem; // do not need this?
Scene::Scene* sceneSystem;
Debug::FrameTimer* frameTimer; //Defining frameTimer for fps

namespace Engine{

    /// <summary>
    /// 
    /// </summary>
    Engine::Engine() : eventBus(std::make_unique<Event::EventBus>()), registry(std::make_unique<ECS::Registry>()), windowWidth(0), windowHeight(0), isRunning(false), main_window(nullptr) {
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
		// TODO: Create game objects...
		registry->AddSystem<System::SMovement>();
        registry->AddSystem<System::SPhysics>();
        registry->AddSystem<System::SRender>();
        registry->AddSystem<System::SKeyboardControl>();
        //sceneSystem->Init();

        ECS::Entity E_RabbitWhite = registry->CreateEntity();
        E_RabbitWhite.AddComponent<Render::CRenderable>();
        E_RabbitWhite.AddComponent<Component::CTransform>(vec2(1.f, 1.f), vec2(2.f, 2.f), 60.f);
        Render::CRenderable& rComp = E_RabbitWhite.GetComponent<Render::CRenderable>();
        rComp.SetTexture("test");
        rComp.SetRenderLayer(Render::CRenderable::R_UI);

        ECS::Entity E_RabbitTest2 = registry->CreateEntity();
        E_RabbitTest2.AddComponent<Render::CRenderable>();
        E_RabbitTest2.AddComponent<Component::CTransform>(vec2(-1.f, -1.f), vec2(2.f, 2.f), 60.f);
        Render::CRenderable& rComp3 = E_RabbitTest2.GetComponent<Render::CRenderable>();
        rComp3.SetTexture("test");
        rComp3.SetRenderLayer(Render::CRenderable::R_BACKGROUND);

        ECS::Entity E_RabbitTest = registry->CreateEntity();
        E_RabbitTest.AddComponent<Render::CRenderable>();
        Render::CRenderable& rComp2 = E_RabbitTest.GetComponent<Render::CRenderable>();
        rComp2.SetColor({ 1.f,0.f,0.f,0.5f });
    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Update() {

        eventBus->Reset();
		//registry->GetSystem<System::SMovement>().Update();
        registry->GetSystem<System::SPhysics>().Update();
        registry->GetSystem<System::SKeyboardControl>().SubscribeToEvents(eventBus);
        registry->Update();
        CheckGLError();
        editor->Update();

        frameTimer.update();
        if(frameTimer.GetFrameCount() == 59)
            std::cout << frameTimer.ReadFPS() << std::endl; //This is what's suppose to be on Editor huhu
        
        // if you want to use Input
        /*
        if (global_input.Action("action name")) // returns true if you want to do it
        */
        global_input.Action("KEY W");
        //global_input.GetKeyReleased(GLFW_KEY_Z); // this is not trigger
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
     //   CheckGLError();
    }

    // HELPER FUNCTIONS
    GLFWwindow* Engine::CreateGLFWwindow(int width, int height)
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