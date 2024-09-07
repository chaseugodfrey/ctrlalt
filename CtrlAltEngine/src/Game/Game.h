/*
* CTRL ALT
@file Game.h
@brief Header file for the Game class
Created by Michael Lazaroo
m.lazaroo@digipen.edu
*/

// PREPROCESSOR DIRECTIVES
// =========================================================================================================
#ifndef GAME_H
#define GAME_H

// INCLUDES
// =========================================================================================================
#include  <GLFW/glfw3.h>

/// spdlog is a lightweight C++ logging class
/// usage
/// 
/// spdlog::trace("TRACE") Loglevel: Trace (Won't show up in console)
/// spdlog::debug("DEBUG") Loglevel: Debug (Won't show up in console)
/// spdlog::info("INFO") Loglevel: Info
/// spdlog::warn("WARN") Loglevel: Warn
/// spdlog::error("ERROR") Loglevel: Error
/// spdlog::critical("CRITICAL") Loglevel: Critical
#include <spdlog/spdlog.h>

// DECLARATIONS
// =========================================================================================================

namespace GameClass
{
	/// <summary>
	/// Uber game class that contains all relevant render and gameplay code
	/// </summary>
	class Game
	{
	private:
		bool isRunning;
		GLFWwindow* window;

	public:
		//constructor/destructor
		Game();
		~Game();

		// initialize the game state, load all textures and levels
		void Initialize();
		void Run();
		void Setup();

		//game loop
		void ProcessInput();
		void Update();
		void Render();

		void Destroy();
		int windowWidth;
		int windowHeight;
	};
}

#endif