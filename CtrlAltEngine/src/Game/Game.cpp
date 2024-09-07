/** 
@group CTRL ALT
@file Game.cpp
@brief Implementation of the Game class
Created by Michael Lazaroo
m.lazaroo@digipen.edu
*/ 


// INCLUDES
// =========================================================================================================
#include "Game.h"
#include <iostream>

// DEFINITIONS
// =========================================================================================================

namespace GameClass {

    /// <summary>
    /// 
    /// </summary>
    Game::Game() : isRunning(false), window(nullptr) {
        spdlog::info("Game constructor called!");
    }

    /// <summary>
    /// 
    /// </summary>
    Game::~Game() {
        spdlog::info("Game destructor called!");
    }

    /// <summary>
    /// 
    /// </summary>
    void Game::Initialize() {
        if (!glfwInit()) {
            spdlog::error("GLFW Failed to Initialize!");
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
            spdlog::error("Failed to create GLFW window");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);

        glViewport(0, 0, windowWidth, windowHeight);
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
            });

        isRunning = true;
    }

    /// <summary>
    /// 
    /// </summary>
    void Game::ProcessInput() {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            isRunning = false;
        }
    }

    /// <summary>
    /// 
    /// </summary>
    void Game::Setup() {
        // TODO: Initialize game objects...
    }

    /// <summary>
    /// 
    /// </summary>
    void Game::Update() {
        // TODO: Update game objects...
    }

    /// <summary>
    /// 
    /// </summary>
    void Game::Render() {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /// <summary>
    /// 
    /// </summary>
    void Game::Run() {
        Setup();
        while (isRunning && !glfwWindowShouldClose(window)) {
            ProcessInput();
            Update();
            Render();
        }
    }

    /// <summary>
    /// 
    /// </summary>
    void Game::Destroy() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}