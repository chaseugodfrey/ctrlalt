/** 
@group CTRL ALT
@file Scene.cpp
@brief Implementation of the Game class
Created by Michael Lazaroo
m.lazaroo@digipen.edu
*/ 


// INCLUDES
// =========================================================================================================
#include "Scene.h"
#include "../ECS/ECS.h"
#include <iostream>
#include "glm/glm.hpp"
#include "../Components/CTransform.h"
#include "../Debug/Debugger.h" //To be added into Logger
#include "../Logger/Logger.h" //Dont need Debugger if this correct

#include "../Editor/Editor.h"

// DEFINITIONS
// =========================================================================================================


namespace Scene{
    //Definitions for Scene namespace
    std::string fps_string[1]; //For fps
    int fpsDisplayDelay = 0;

    /// <summary>
    /// 
    /// </summary>
    Scene::Scene() : registry(std::make_unique<ECS::Registry>()), isRunning(false), window(nullptr) {
        Logger::LogMessage(LOG_INFO, "Scene Created");
    }

    /// <summary>
    /// 
    /// </summary>
    Scene::~Scene() {
        Logger::LogMessage(LOG_INFO, "Scene Deleted");
    }

    /// <summary>
    /// 
    /// </summary>
    void Scene::Initialize() {
        if (!glfwInit()) {
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        windowWidth = mode->width;
        windowHeight = mode->height;

        //window = glfwCreateWindow(windowWidth, windowHeight, "AxelUnderland", glfwGetPrimaryMonitor(), nullptr); //Fullscreen
        window = glfwCreateWindow(windowWidth, windowHeight, "AxelUnderland", NULL, nullptr); //Windowed
        if (!window) {

            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);

        glViewport(0, 0, windowWidth, windowHeight);
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
            }); 

        GameEditor::Activate(window);

        isRunning = true;
        //endFrameTime = std::chrono::high_resolution_clock::now(); //FPS related, not needed
    }

    /// <summary>
    /// 
    /// </summary>
    void Scene::ProcessInput() {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            isRunning = false;
        }
    }

    /// <summary>
    /// 
    /// </summary>
    void Scene::Setup() {
		// TODO: Create game objects...
		ECS::Entity E_Player = registry->CreateEntity();
		ECS::Entity E_RabbitWhite = registry->CreateEntity();
		ECS::Entity E_RabbitBlack = registry->CreateEntity();
        registry->AddComponent<Component::CTransform>(E_Player, glm::vec2(10.0, 30.0), glm::vec2(1.0, 1.0), 60.0);

   
    }

    /// <summary>
    /// 
    /// </summary>
    void Scene::Update() {
        Debug::fpsUpdate(fps_string); //FPS tracker to be implemmeneted into LogMessage
        if (fpsDisplayDelay == 60) {
            Logger::LogMessage(LOG_INFO, "FPS: " + *fps_string); //FPS Tracker implemented onto logger, need to reformat texts //TBA toggling
            fpsDisplayDelay = 0;
        }
        fpsDisplayDelay++;
    }

    /// <summary>
    /// 
    /// </summary>
    void Scene::Render() {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        {
            // IMGUI
            GameEditor::Run();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    /// <summary>
    /// 
    /// </summary>
    void Scene::Run() {
        Setup();
        while (isRunning && !glfwWindowShouldClose(window) && !GameEditor::GetExitPrompt()) {
            ProcessInput();
            Update();
            Render();
        }
    }

    /// <summary>
    /// 
    /// </summary>
    void Scene::Destroy() {

        {
            // IMGUI
            GameEditor::Terminate();
        }


        glfwDestroyWindow(window);
        glfwTerminate();
    }
}