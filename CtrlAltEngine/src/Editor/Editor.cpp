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

	static Editor* editor = nullptr;

	Editor const* GetEditor()
	{
		return editor;
	}

	// TESTING STUFF
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

	/////////////////////////////////////////////////////////

	Editor::Editor() : window(nullptr)
	{
		//Logger::LogInfo("Editor Created");
		editor = this;
	};

	Editor::~Editor()
	{
		//Logger::LogInfo("Editor Created");
	}

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

		//gui_windows_list.push_back()
	}

	void Editor::Update()
	{
		glfwPollEvents();

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
		DisplayFPS();

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

	// To Do:
	// Delete as function has been relocated
	void Editor::DisplayFPS()
	{

	}

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

	void Editor::DisplayScene()
	{
		//ImGui::SetNextWindowSize(ImVec2(1120, 500));
		//ImGui::SetNextWindowPos(ImVec2(400, 40));

		if (ImGui::Begin("Scene", NULL))
		{


		}

		ImGui::End();

	}

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

			
			if (ImGui::BeginTable("Console_Table", 1, ImGuiTableFlags_Borders | ImGuiTableFlags_BordersInner | ImGuiTableRowFlags_Headers | ImGuiTableFlags_ScrollY))
			{

				for (size_t i = 0; i < console_data.size(); i++)
				{

					ImGui::TableNextRow(NULL, 25.0f);
					ImGui::TableNextColumn();
					ImGui::Text(console_data[i].c_str());
				}

				ImGui::EndTable();
			}

		}

		ImGui::End();
	}


	bool Editor::GetExitPrompt()
	{
		return isPromptedToExit;
	}

	void Editor::ConsoleAddLine(std::string const& str) const
	{
		console_data.push_back(str);
	}

	void Editor::ConsoleClear() const
	{
		console_data.clear();
	}

	std::string Editor::ReadFPS() const
	{
		std::string FPSCOUNT = "FPS + " + frame_timer->ReadFPS();
		return FPSCOUNT;
	}

	void Editor::LoadScene(int index)
	{
		ConsoleAddLine("Scene Loaded: " + std::to_string(index));
		std::string this_string = "Scene" + std::to_string(index);
		scene_manager->SwitchScene(this_string);
	}

	//}
}