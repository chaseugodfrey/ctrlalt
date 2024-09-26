/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Editor.cpp
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Sep 08, 2024
\brief

Defines


Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Editor.h"
#include <string>

#include <fstream>
#include <iostream>
#include <vector>

namespace GameEditor
{

	// TESTING STUFF
	std::string file_path{ "Resources/test.txt" };
	std::string test_text{};

	std::vector<std::string> console_logs;
	void deserialize_string()
	{
		std::ifstream ifs{ "Resources/test.txt" };
		if (!ifs.is_open())
			assert(false && "no file");
		ifs.close();
	}

	void serialize_string()
	{
		std::ofstream ofs{ "Resources/test.txt" };
		ofs.close();
	}

	Editor::Editor() : window(nullptr)
	{

	};

	Editor::~Editor()
	{

	}

	void Editor::Initialize(GLFWwindow* _window)
	{
		window = _window;
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

		if (isPromptedToExit)
		{

		}
	}

	// FOR RENDERING
	void Editor::Draw()
	{
		glfwMakeContextCurrent(window);
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		DisplayMenuBar();

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

		// Menu Bar Rendering
		if (ImGui::Begin("AxelUnderland", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking))
		{
			if (ImGui::BeginMenuBar())
			{

				// FILE DROP DOWN MENU
				if (ImGui::BeginMenu("File"))
				{
					ImGui::MenuItem("Exit", NULL, &isPromptedToExit);
					ImGui::EndMenu();

				}

				if (ImGui::BeginMenu("Create"))
				{
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

		};

		ImGui::End();

	}

	void Editor::DisplayFPS()
	{
		//ImGui::SetNextWindowSize(ImVec2(100, 100));

		if (ImGui::Begin("FPS", NULL, ImGuiWindowFlags_NoCollapse))
		{
			static int fps_counter = 0;
			std::string fps_counter_str;
			fps_counter_str = std::to_string(fps_counter++);

			ImGui::Text(fps_counter_str.c_str());

		}

		ImGui::End();

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
			int action = 0;
			/*if (ImGui::Button("Clear"))
				action = 1;*/

			if (ImGui::BeginTable("Console_Table", 1, ImGuiTableFlags_Borders | ImGuiTableFlags_BordersInner | ImGuiTableRowFlags_Headers))
			{

				for (size_t i = 0; i < console_logs.size(); i++)
				{
					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					//ImGui::Text(console_logs[i].c_str());
					ImGui::Text("Words");
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

	//}
}