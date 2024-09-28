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

#include "../Render/Render.h"


// DEFINITIONS
// =========================================================================================================

//Render::RenderPipeline renderSystem;
Input::Input_Container global_input;// definition of the global variable 

namespace Engine{

    /// <summary>
    /// 
    /// </summary>
    Engine::Engine() : registry(std::make_unique<ECS::Registry>()), windowWidth(0), windowHeight(0), isRunning(false), main_window(nullptr) {
        //Logger::LogInfo("Engine Created");
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
        main_window = CreateGLFWwindow(windowWidth, windowHeight);

        // INITIALIZE SYSTEMS HERE
       // renderSystem.Init();
        editor = new GameEditor::Editor();
        editor->Initialize(main_window);

        isRunning = true;

        //## initialise input systems,
        // key binds WASD, 1 rot, 2 scale.
        //## my input system will be a static variable in header.
        global_input.Init_System(main_window); 
        

    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::ProcessInput() {
        if (glfwGetKey(main_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            isRunning = false;
        }
        global_input.UpdateActionState(main_window); // able to dynamically change windows for keychecks
    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Setup() {
		// TODO: Create game objects...
		registry->AddSystem<System::SMovement>();
        registry->AddSystem<System::SRender>();

		ECS::Entity E_Player = registry->CreateEntity();
		ECS::Entity E_RabbitWhite = registry->CreateEntity();
		ECS::Entity E_RabbitBlack = registry->CreateEntity();

        E_Player.AddComponent<Component::CTransform>(glm::vec2(10.0, 30.0), glm::vec2(1.0, 1.0), 60.0);
		E_Player.AddComponent<Component::CRigidBody>(glm::vec2(10.0, 30.0));

    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Update() {

		registry->GetSystem<System::SMovement>().Update();

        registry->Update();
        editor->Update();

        
        // if you want to use Input
        /*
        if (global_input.Action("action name")) // returns true if you want to do it
        */
        global_input.Action("KEY W");
        //global_input.GetKeyReleased(GLFW_KEY_Z); // this is not trigger
    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Render() {

        // SET BACKGROUND
        //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        registry->GetSystem<System::SRender>().Render();
        editor->Draw();

        glfwSwapBuffers(main_window);
        glfwPollEvents();

    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Run() {
        Setup();
        while (isRunning && !glfwWindowShouldClose(main_window) && !editor->GetExitPrompt()) {
            ProcessInput();
            Update();
            Render();
        }
    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Destroy() {
        editor->Destroy();
        glfwDestroyWindow(main_window);
        glfwTerminate();
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
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
            });

        return window;
    }

}