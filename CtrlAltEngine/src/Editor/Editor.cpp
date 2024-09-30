/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Editor.cpp
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Sep 08, 2024
\brief

Defines

 ====== Helpful code ======

 For static GUI items that don't move:
 *		ImGui::SetNextWindowSize(ImVec2(x, y));
 *		ImGui::SetNextWindowPos(ImVec2(x, y)); 


 For padding, use:
 *		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ...); 
		/code/
		ImGui::PopStyleVar()

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
#include <sstream>

namespace Editor
{

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
	};

	Editor::~Editor()
	{
		//Logger::LogInfo("Editor Created");
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

		// =========== TESTING PURPOSES =============

		if (ImGui::IsKeyPressed(ImGuiKey_A))
		{
			static int count = 1;
			ConsoleAddLine(std::to_string(count++));

		}

		if (isCreateEntity)
		{
			ConsoleAddLine("Object created.");
			isCreateEntity = false;
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
					ImGui::EndMenu();

				}

				if (ImGui::BeginMenu("Create"))
				{
					ImGui::MenuItem("Entity", NULL, &isCreateEntity);
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
			ImGui::Button("A", btn_size); ImGui::SameLine();
			ImGui::Dummy(btn_size); ImGui::SameLine();
			ImGui::Button("B", btn_size);
		}

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
					//ImGui::Text("Words");
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

	void Editor::ConsoleAddLine(std::string const& str)
	{
		console_data.push_back(str);
	}

	void Editor::ConsoleClear()
	{
		console_data.clear();
	}



	//}
}