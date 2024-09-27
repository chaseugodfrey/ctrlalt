#ifndef EDITOR_H
#define EDITOR_H

#include  <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <vector>

#include "Editor_Includes.h"
#include "EditorWindow.h"


namespace GameEditor {

	class Editor {

	private:

		// bools
		bool isPromptedToExit{ false };

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

		// Get bools
		bool GetExitPrompt();
	};

}



#endif