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
#include "../ECS/ECS.h"
#include <iostream>
#include "glm/glm.hpp"
#include "../Components/CTransform.h"
#include "../Components/CRigidBody.h"
#include "../Systems/SMovement.h"
#include "../Systems/SPhysics.h"
#include "../Math/MathLib.h"

#include "../Render/Render.h"


// DEFINITIONS
// =========================================================================================================

//Render::RenderPipeline renderSystem;

namespace Engine{

    /// <summary>
    /// 
    /// </summary>
    Engine::Engine() : registry(std::make_unique<ECS::Registry>()), windowWidth(0), windowHeight(0), isRunning(false), main_window(nullptr) {
        Logger::LogInfo("Engine Created");
    }

    /// <summary>
    /// 
    /// </summary>
    Engine::~Engine() {
        Logger::LogInfo("Engine Deleted");
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

        // INITIALIZE SYSTEMS HERE
       // renderSystem.Init();
        editor = new GameEditor::Editor();
        editor->Initialize(main_window);

        isRunning = true;
    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::ProcessInput() {
        if (glfwGetKey(main_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            isRunning = false;
        }
    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Setup() {
		// TODO: Create game objects...
		registry->AddSystem<System::SMovement>();
        //change this
        registry->AddSystem<System::SPhysics>();
        registry->AddSystem<System::SRender>();

        CheckGLError();
		ECS::Entity E_Player = registry->CreateEntity();
		ECS::Entity E_RabbitBlack = registry->CreateEntity();

        //change this
        E_Player.AddComponent<Component::CTransform>(MathLib::vec2(10.0, 30.0), MathLib::vec2(1.0, 1.0), 60.0);
		E_Player.AddComponent<Component::CRigidBody>(MathLib::vec2(10.0, 30.0));

        ECS::Entity E_RabbitWhite = registry->CreateEntity();
        E_RabbitWhite.AddComponent<Render::CRenderable>();
        E_RabbitWhite.AddComponent<Component::CTransform>(MathLib::vec2(1.f, 1.f), MathLib::vec2(2.f, 2.f), 60.f);
        Render::CRenderable& rComp = E_RabbitWhite.GetComponent<Render::CRenderable>();
        rComp.SetTexture("test");
        rComp.SetRenderLayer(Render::CRenderable::R_UI);

        ECS::Entity E_RabbitTest2 = registry->CreateEntity();
        E_RabbitTest2.AddComponent<Render::CRenderable>();
        E_RabbitTest2.AddComponent<Component::CTransform>(MathLib::vec2(-1.f, -1.f), MathLib::vec2(2.f, 2.f));
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

		registry->GetSystem<System::SMovement>().Update();
        CheckGLError();

        registry->Update();
        CheckGLError();
        editor->Update();
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