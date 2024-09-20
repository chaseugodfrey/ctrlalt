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
#include "../Components/CRigidBody.h"
#include "../Systems/SMovement.h"

#include "../Editor/Editor.h"

#include "../Render/Render.h"

// DEFINITIONS
// =========================================================================================================

Render::RenderPipeline renderSystem;
namespace Scene{

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

        window = glfwCreateWindow(windowWidth, windowHeight, "AxelUnderland", glfwGetPrimaryMonitor(), nullptr);
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

        renderSystem.Init();

        isRunning = true;
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
		registry->AddSystem<System::SMovement>();

		ECS::Entity E_Player = registry->CreateEntity();
		ECS::Entity E_RabbitWhite = registry->CreateEntity();
		ECS::Entity E_RabbitBlack = registry->CreateEntity();

        E_Player.AddComponent<Component::CTransform>(glm::vec2(10.0, 30.0), glm::vec2(1.0, 1.0), 60.0);
		E_Player.AddComponent<Component::CRigidBody>(glm::vec2(10.0, 30.0));

    }

    /// <summary>
    /// 
    /// </summary>
    void Scene::Update() {

		registry->GetSystem<System::SMovement>().Update();

        registry->Update();
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
            renderSystem.Draw();
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