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
#include "../Systems/SKeyboardControl.h"
#include "../Scene/Scene.h"
#include "../Render/Render.h"


// DEFINITIONS
// =========================================================================================================

//Render::RenderPipeline renderSystem; // do not need this?
Scene::Scene* sceneSystem;

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
        Logger::LogInfo("Engine Deleted");
    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Initialize() {


        //sceneManager = std::make_unique<Scene::SceneManager>(registry.get());
        //sceneManager->AddScene("Scene1", "Assets/scene1.txt");
        //sceneManager->AddScene("Scene2", "Assets/scene2.txt");
        //sceneManager->AddScene("Scene3", "Assets/scene3.txt");
        //sceneManager->SwitchScene("Scene1");


        if (!glfwInit()) {
            return;
        }

        // CREATE WINDOWED APPLICATION
        main_window = CreateGLFWwindow(windowWidth, windowHeight);

        // INITIALIZE SYSTEMS HERE
       // renderSystem.Init();
        editor = new GameEditor::Editor();
        editor->Initialize(main_window);
        sceneSystem = new Scene::Scene(registry.get());

        isRunning = true;
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
    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Setup() {
		// TODO: Create game objects...
		registry->AddSystem<System::SMovement>();
        registry->AddSystem<System::SRender>();
        registry->AddSystem<System::SKeyboardControl>();
        //sceneSystem->Init();

    }

    /// <summary>
    /// 
    /// </summary>
    void Engine::Update() {

        eventBus->Reset();
		registry->GetSystem<System::SMovement>().Update();
        registry->GetSystem<System::SKeyboardControl>().SubscribeToEvents(eventBus);
        registry->Update();
        editor->Update();
        //sceneManager->UpdateScene();
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
            glfwPollEvents();
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