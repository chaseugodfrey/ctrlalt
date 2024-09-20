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
#include "thread" //Simulated workload for FPS
//#include "../Debug/Debugger.h"

#include "../Editor/Editor.h"

// DEFINITIONS
// =========================================================================================================


namespace Scene{
    //Definitions for Scene namespace
    auto endFrameTime = std::chrono::high_resolution_clock::now(); //Tracker for FPS, init with value first so auto knows the type
    int framecount = 0; //Counter for FPS
    std::chrono::duration<double> elapsedDurationBetweenFrames;


    /// <summary>
    /// 
    /// </summary>
    Scene::Scene() : registry(std::make_unique<ECS::Registry>()), isRunning(false), window(nullptr) {
        Logger::LogInfo("Scene Created");
    }

    /// <summary>
    /// 
    /// </summary>
    Scene::~Scene() {
        Logger::LogInfo("Scene Deleted");
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
        endFrameTime = std::chrono::high_resolution_clock::now();
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
        //Debug::fpsUpdate();
        //Start of FPS Tracker
        //Get time of new frame start
        auto startFrameTime = std::chrono::high_resolution_clock::now();
        //std::this_thread::sleep_for(std::chrono::milliseconds(8)); //Simulated workload, when rendering and stuff happens this can be removed
        framecount++;
        if ((startFrameTime - endFrameTime).count() > 0.01667f) // 1/60
            elapsedDurationBetweenFrames += static_cast<std::chrono::duration<double>> (0.01667f);
        else
            elapsedDurationBetweenFrames += startFrameTime - endFrameTime;
        //Calculate time between frames if
        //Display difference
        if (framecount == 60) {
            //std::chrono::duration<double> duration = start - end;
            auto fps = framecount / elapsedDurationBetweenFrames.count();
            std::cout << "FPS: " << fps << std::endl;
            framecount = 0;             //reset to 0
            elapsedDurationBetweenFrames = startFrameTime - startFrameTime;   //reset to 0
        }//End of FPS tracker, unsure if works correctly currently using simulated workload
        endFrameTime = startFrameTime;
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