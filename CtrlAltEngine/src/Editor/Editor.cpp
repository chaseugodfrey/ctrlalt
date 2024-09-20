#include "Editor.h"

#include "../../imgui/include/imgui.h"
#include "../../imgui/include/imgui_impl_glfw.h"
#include "../../imgui/include/imgui_impl_opengl3.h"

namespace GameEditor
{



	// Compulsory set up for initialization of IMGUI

	Editor::Editor() : window(nullptr) 
	{

	};

	Editor::~Editor()
	{

	}

	void Editor::Load(GLFWwindow* _window)
	{
		window = _window;
	}

	void Editor::Initialize()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 450");
	}
	
	void Editor::Update()
	{
		if (isPromptedToExit)
		{

		}
	}

	void Editor::Render()
	{
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		DisplayMenuBar();
		DisplayHierachy();
		DisplayInspector();
		DisplayScene();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Editor::Destroy()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	bool Editor::GetExitPrompt()
	{
		return isPromptedToExit;
	}

	bool GetExitPrompt()
	{
		return editor.GetExitPrompt();
	}

	void Activate(GLFWwindow* _window)
	{
		editor.Load(_window);
		editor.Initialize();
	}

	void Run()
	{
		editor.Render();
	}

	void Terminate()
	{
		editor.Destroy();
	}

	// EDITOR WINDOWS

	void Editor::DisplayMenuBar()
	{
		// Set Menu Bar Size & position
		// Remember to change size dynamically
		ImGui::SetNextWindowSize(ImVec2(1920, 40));
		ImGui::SetNextWindowPos(ImVec2(0, 0));

		// Menu Bar Rendering
		if (ImGui::Begin("AxelUnderland", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
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

			ImGui::End();
		};

	}

	void Editor::DisplayInspector()
	{
		ImGui::SetNextWindowSize(ImVec2(400, 500));
		ImGui::SetNextWindowPos(ImVec2(0, 40));

		if (ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoCollapse ))
		{
			if (ImGui::TreeNode("Transform"))
			{
				static float coord[2]{ 0, 0 };
				ImGui::DragFloat2("x: ", coord);
				ImGui::TreePop();
			}

			ImGui::End();
		}
	}

	void Editor::DisplayHierachy()
	{
		ImGui::SetNextWindowSize(ImVec2(400, 500));
		ImGui::SetNextWindowPos(ImVec2(1920 - 400, 40));

		if (ImGui::Begin("Hierachy", NULL, ImGuiWindowFlags_NoCollapse))
		{


			ImGui::End();
		}
	}

	void Editor::DisplayScene()
	{
		ImGui::SetNextWindowSize(ImVec2(1120, 500));
		ImGui::SetNextWindowPos(ImVec2(400, 40));

		if (ImGui::Begin("Scene", NULL, ImGuiWindowFlags_NoCollapse))
		{


			ImGui::End();
		}
	}

	//void Editor::DisplayInConsole()
	//{

	//}
}