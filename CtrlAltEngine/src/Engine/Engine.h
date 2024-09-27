/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Engine.h
\author 	Michael Lazaroo
\par    	m.lazaroo@digipen.edu
\date   	Sep 08, 2024
\brief


Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

// PREPROCESSOR DIRECTIVES
// =========================================================================================================
#ifndef ENGINE_H
#define ENGINE_H

// This is here because= GLFW uses the APIENTRY macro to declare the same name function, both have windows.h  files
#ifdef _WIN32
#include <windows.h>
#else
#define APIENTRY
#endif


// INCLUDES
// =========================================================================================================

#include <GLEW/GL/glew.h>
#include <GLFW/glfw3.h>\

/// spdlog is a lightweight C++ logging class
/// usage
/// 
/// spdlog::trace("TRACE") Loglevel: Trace (Won't show up in console)
/// spdlog::debug("DEBUG") Loglevel: Debug (Won't show up in console)
/// spdlog::info("INFO") Loglevel: Info
/// spdlog::warn("WARN") Loglevel: Warn
/// spdlog::error("ERROR") Loglevel: Error
/// spdlog::critical("CRITICAL") Loglevel: Critical
#include "../ECS/ECS.h"
#include "../Scene/Scene.h"
#include "../Editor/Editor.h"

// DECLARATIONS
// =========================================================================================================

namespace Engine
{
	/// <summary>
	/// Uber game class that contains all relevant render and gameplay code
	/// </summary>
	/// 


	class Engine
	{
	private:
		bool isRunning;
		GLFWwindow* main_window;

		std::unique_ptr<ECS::Registry> registry;
		GameEditor::Editor* editor;
		GLFWwindow* CreateGLFWwindow(int width, int height);

	public:
		//constructor/destructor
		Engine();
		~Engine();

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