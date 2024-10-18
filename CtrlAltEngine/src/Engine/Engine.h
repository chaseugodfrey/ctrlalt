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


// INCLUDES
// =========================================================================================================
//
//#include <GLEW/GL/glew.h>
//#include <GLFW/glfw3.h>

#include "../ECS/ECS.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Render/Render.h"
#include "../Editor/Editor.h"
#include "../EventManager/EventBus.h"
#include "../AssetManager/AssetManager.h"
#include "../Input/Input.h"
#include "../Debug/Debugger.h"

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

		//ECS
		std::unique_ptr<ECS::Registry> registry;
		std::unique_ptr<Event::EventBus> eventBus;
		std::unique_ptr<Scene::SceneManager> sceneManager;
		
		//Editor
		Editor::Editor* editor;

		//Asset
		AssetManager assetManager; 

		//FrameTimer
		Debug::FrameTimer frameTimer;

		//GLFWwindow* CreateGLFWwindow(int width, int height);

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

	};


}

#endif