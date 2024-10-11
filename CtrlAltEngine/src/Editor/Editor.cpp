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

namespace Editor
{

	//========================================================
	//========================================================
	//========================================================

	// TESTING PURPOSES
	static Editor* editor = nullptr;

	Editor const* GetEditor()
	{
		return editor;
	}

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

	Editor::Editor() : window(nullptr), frame_timer(nullptr), scene_manager(nullptr)
	{
		//Logger::LogInfo("Editor Created");
		editor = this;
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

	void Editor::Initialize(GLFWwindow* _window, Scene::SceneManager* _scene_manager, Debug::FrameTimer* _frameTimer)
	{
		//Dependencies
		window = _window;
		scene_manager = _scene_manager;
		frame_timer = _frameTimer;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
		ImGui_ImplOpenGL3_Init("#version 450");

		deserialize_string();
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

	void Editor::Draw()
	{
		glfwMakeContextCurrent(window);
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		// To Do:
		// Convert into separate window file sub classes
		DisplayMenuBar();
		DisplayPlayState();
		DisplayInspector();
		DisplayScene();
		DisplayInConsole();

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

	void Editor::DisplayMenuBar()
	{
		// Set Menu Bar Size & position
		// Remember to change size dynamically
		ImGui::SetNextWindowSize(ImVec2(1920, 40));
		ImGui::SetNextWindowPos(ImVec2(0, 0));

		static ImVec2 frame_padding(5.0f, 10.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, frame_padding);

		// Menu Bar Rendering
		if (ImGui::Begin("AxelUnderland", NULL,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking))
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::SetWindowFontScale(1.2f);
				// FILE DROP DOWN MENU
				if (ImGui::BeginMenu("File"))
				{
					ImGui::MenuItem("Exit", NULL, &isPromptedToExit);

					// DISABLE SAVE SCENE FOR NOW
					//if (ImGui::MenuItem("Save Scene"))
					//{
					//	scene_manager->SaveScene();
					//}

					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Create"))
				{
					//ImGui::BeginDisabled();

					if (ImGui::MenuItem("Entity (WIP)"))
					{
						scene_manager->CreateEntityInScene("Basic");
						//ECS::Entity entity = registry->CreateEntity();

					}
					//ImGui::EndDisabled();
					ImGui::EndMenu();
				}

				// FOR M1 SUBMISSION PURPOSES
				if (ImGui::BeginMenu("M1 Scenes"))
				{
					if (ImGui::MenuItem("Scene 1"))
					{
						LoadScene(1);
					};

					if (ImGui::MenuItem("Scene 2"))
					{
						LoadScene(2);
					};

					if (ImGui::MenuItem("Scene 3"))
					{
						LoadScene(3);
					};

					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

		};

		ImGui::PopStyleVar();
		ImGui::End();

	}

	/**
	 * @brief Displays the play state window in the editor.
	 *
	 * This function sets up and renders the play state window, which includes buttons
	 * for "Play" and "Stop", as well as displaying the current frames per second (FPS).
	 *
	 * @return void This function does not return a value.
	 */

	void Editor::DisplayPlayState()
	{

		ImGui::SetNextWindowSize(ImVec2(1920, 40));
		ImGui::SetNextWindowPos(ImVec2(0, 40));

		if (ImGui::Begin("PlayState", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar))
		{

			ImVec2 btn_size(36, 20);
			ImGui::SameLine(ImGui::GetWindowWidth() * 0.5f);
			ImGui::Button("Play", btn_size); ImGui::SameLine();
			ImGui::Dummy(btn_size); ImGui::SameLine();
			ImGui::Button("Stop", btn_size);
		}

		ImGui::SameLine(ImGui::GetWindowWidth() * 0.95f);
		ImGui::Text(ReadFPS().c_str());
	

		ImGui::End();
	}

	/**
	 * @brief Displays the inspector window in the editor.
	 *
	 * This function creates and renders the inspector window, allowing users to view
	 * and edit entity properties such as "Transform". It includes drag-and-drop for
	 * modifying position coordinates and an input text field for serialization testing.
	 *
	 * @return void This function does not return a value.
	 */

	void Editor::DisplayInspector()
	{
		//ImGui::SetNextWindowSize(ImVec2(400, 500));
		//ImGui::SetNextWindowPos(ImVec2(0, 40));

		if (ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoCollapse ))
		{
			if (ImGui::TreeNode("Transform"))
			{
				static float coord[2]{ 0, 0 };
				ImGui::DragFloat2("x: ", coord);
				ImGui::TreePop();
			}

			if (ImGui::InputText("Serialize Test", &test_text))
			{

			}

		}

		ImGui::End();
	}

	void Editor::DisplayHierarchy()
	{
		//ImGui::SetNextWindowSize(ImVec2(400, 500));
		//ImGui::SetNextWindowPos(ImVec2(1920 - 400, 40));

	}

	/**
	 * @brief Displays scene window in the editor.
	 *
	 * This function displays the scene rendered as a frame buffer
	 * from the rendering system after converting it into an ImGUI
	 * texture.
	 * 
	 * Not currently working now.
	 *
	 * @return void This function does not return a value.
	 */

	void Editor::DisplayScene()
	{
		//ImGui::SetNextWindowSize(ImVec2(1120, 500));
		//ImGui::SetNextWindowPos(ImVec2(400, 40));

		if (ImGui::Begin("Scene", NULL))
		{


		}

		ImGui::End();

	}

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

	void Editor::DisplayInConsole()
	{
		//ImGui::SetNextWindowSize(ImVec2(800, 500));
		//ImGui::SetNextWindowPos(ImVec2(400, 500));
		

		if (ImGui::Begin("Console", NULL, ImGuiWindowFlags_NoCollapse))
		{

			if (ImGui::Button("Clear"))
			{
				ConsoleClear();
			}

			static bool auto_scroll = true;
			static float scroll_pos = 0.f;

			if (ImGui::BeginTable("Console_Table", 1, ImGuiTableFlags_Borders | ImGuiTableFlags_BordersInner | ImGuiTableRowFlags_Headers | ImGuiTableFlags_ScrollY))
			{

				for (size_t i = 0; i < console_data.size(); i++)
				{
					ImGui::TableNextRow(NULL, 25.0f);
					ImGui::TableNextColumn();
					ImGui::Text(console_data[i].c_str());
				}

				if (auto_scroll)
					ImGui::SetScrollY(ImGui::GetScrollMaxY());

				if (ImGui::GetScrollY() < ImGui::GetScrollMaxY() - 10.0f)
					auto_scroll = false;
				else
					auto_scroll = true;


			
				ImGui::EndTable();
			}

		}

		ImGui::End();
	}

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
	 * @brief Clears the console log.
	 *
	 * This function clears all the text currently stored in the console's log.
	 *
	 * @return void This function does not return a value.
	 */

	void Editor::ConsoleClear() const
	{
		console_data.clear();
	}

	/**
	 * @brief Reads and returns the current frames per second (FPS).
	 *
	 * This function retrieves the current FPS from the frame timer and formats it
	 * as a string.
	 *
	 * @return std::string A formatted string showing the current FPS.
	 */

	std::string Editor::ReadFPS() const
	{
		std::string FPSCOUNT = "FPS + " + frame_timer->ReadFPS();
		return FPSCOUNT;
	}

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