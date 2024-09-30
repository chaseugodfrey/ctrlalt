#ifndef EDITOR_H
#define EDITOR_H

#include  <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <vector>

#include "Editor_Includes.h"
#include "EditorWindow.h"


namespace Editor {

	class Editor {

	private:

		// bools
		bool isPromptedToExit{ false };
		bool isCreateEntity{ false };

		GLFWwindow* window;

		std::vector<EditorWindow*> gui_windows_list;

		void DisplayMenuBar();
		void DisplayPlayState();
		void DisplayFPS();
		void DisplayHierarchy();
		void DisplayInspector();
		void DisplayScene();
		void DisplayInConsole();

	public:
		Editor();
		~Editor();

		void Initialize(GLFWwindow* window);
		void Update();
		void Draw();
		void Destroy();

		// TEST FUNCTIONS
		void ConsoleAddLine(std::string const&);
		void ConsoleClear();

		// Get bools
		bool GetExitPrompt();

	};

}


// GLOBAL TEST FUNCTIONS





#endif