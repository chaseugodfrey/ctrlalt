/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Editor.cpp
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Sep 08, 2024
\brief

ImGui Editor Interface to wrap engine functionality and display necessary information
for editing scenes.

 ====== Helpful ImGui Code ======

 For static GUI items that don't move:
 *		ImGui::SetNextWindowSize(ImVec2(x, y));
 *		ImGui::SetNextWindowPos(ImVec2(x, y)); 


 For padding, use:
 *		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ...); 
		/code/
		ImGui::PopStyleVar()

For layout
*		ImGui::Dummy();
*		ImGui::SameLine(); -> can input window positions for offset as well

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "Editor.h"
#include "../EventManager/EventBus.h"
#include "../ECS/ECS.h"
#include "../Scene/SceneManager.h"

namespace CtrlAltEditor
{

	//========================================================
	//========================================================
	//========================================================

	// TESTING PURPOSES

	std::string file_path{ "Resources/test.txt" };
	std::string test_text{};

	std::vector<std::string> console_data;
	void deserialize_string()
	{
		std::ifstream ifs{ "Resources/test.txt" };
		if (ifs.is_open())
		{
			/*assert(false && "no file");*/
			ifs >> test_text;
			std::cout << "deserialized " << test_text << std::endl;
		}
		ifs.close();
	}

	void serialize_string()
	{
		std::ofstream ofs{ "Resources/test.txt" };
		std::cout << "serializing " << test_text << std::endl;
		ofs << test_text;
		ofs.close();
	}

	//========================================================
	//========================================================
	//========================================================

	Editor::Editor()
	{
		//Logger::LogInfo("Editor Created");
	};

	Editor::~Editor()
	{

		//Logger::LogInfo("Editor Created");
	}

	/**
	 * @brief Initializes the editor with necessary dependencies and ImGui setup.
	 *
	 * This function sets up the editor by initializing the window, scene manager,
	 * and frame timer. It also configures the ImGui context and docking settings.
	 *
	 * @param _window A pointer to the GLFW window used by the editor.
	 * @param _scene_manager A pointer to the scene manager responsible for scene handling.
	 * @param _frameTimer A pointer to the frame timer used to track FPS and other time-based functionality.
	 *
	 * @return void This function does not return a value.
	 */

	void Editor::Initialize(GLFWwindow* window, Scene::SceneManager* _scene_manager, Debug::FrameTimer* _frameTimer)
	{

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
		ImGui_ImplOpenGL3_Init("#version 450");

		deserialize_string();

		context = std::make_unique<EditorContext>();
		service = std::make_unique<EditorService>(*context.get(), *_frameTimer);
		service->CreateEditorWindow(MENUBAR);
		service->CreateEditorWindow(PLAYBAR);
		service->CreateEditorWindow(SCENE);
		service->CreateEditorWindow(HIERARCHY);
		service->CreateEditorWindow(INSPECTOR);
		service->CreateEditorWindow(CONSOLE);
	}

	void Editor::Update()
	{
		//glfwPollEvents(); // unsure if extra polling?

		// =========== TESTING PURPOSES =============

		if (ImGui::IsKeyPressed(ImGuiKey_A))
		{
			static int count = 1;
			ConsoleAddLine(std::to_string(count++));
		}

		if (isPromptedToExit)
		{

		}

		// ===========================================
	}

	void Editor::Render(GLFWwindow* window)
	{
		// ImGUI Set New Frames
		glfwMakeContextCurrent(window);
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		//
		DisplayGUIWindows();

		// ImGUI Render
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Editor::Destroy()
	{
		serialize_string();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Editor::DisplayGUIWindows()
	{
		if (context->windowList.size() <= 0)
			return;

		for (auto& window : context->windowList)
		{
			window->Display();
		}
	}

	// EDITOR WINDOWS

	/**
	 * @brief Displays the menu bar for the editor window.
	 *
	 * This function creates and renders the editor's menu bar, including menus for "File",
	 * "Create", and "M1 Scenes", with options like exiting the program, creating entities,
	 * and loading scenes.
	 *
	 * @return void This function does not return a value.
	 */



	/**
	 * @brief Displays the console window in the editor.
	 *
	 * This function sets up and renders the console window, allowing users to view
	 * and clear console messages. It features a scrollable table displaying logged data,
	 * with an option for auto-scrolling. Users can also manually clear the console
	 * by pressing the "Clear" button.
	 *
	 * @return void This function does not return a value.
	 */


	/**
	 * @brief Retrieves the exit prompt status.
	 *
	 * This function checks whether the user has been prompted to exit the editor.
	 *
	 * @return bool True if the user is prompted to exit, false otherwise.
	 */

	bool Editor::GetExitPrompt()
	{
		return isPromptedToExit;
	}

	/**
	 * @brief Adds a new line of text to the console.
	 * 
	 * This function appends a given string to the console's log.
	 * 
	 * @param str The string to be added to the console.
	 * @return void This function does not return a value.
	 */

	void Editor::ConsoleAddLine(std::string const& str) const
	{
		console_data.push_back(str);
	}



	/**
	 * @brief Reads and returns the current frames per second (FPS).
	 *
	 * This function retrieves the current FPS from the frame timer and formats it
	 * as a string.
	 *
	 * @return std::string A formatted string showing the current FPS.
	 */

	/**
	 * @brief Loads a scene based on its index.
	 *
	 * This function logs a message to the console and switches to a new scene
	 * by its index.
	 *
	 * @param index The index of the scene to load.
	 * @return void This function does not return a value.
	 */

	void Editor::LoadScene(int index)
	{
		ConsoleAddLine("Scene Loaded: " + std::to_string(index));
		std::string this_string = "Scene" + std::to_string(index);
		scene_manager->SwitchScene(this_string);
	}

}