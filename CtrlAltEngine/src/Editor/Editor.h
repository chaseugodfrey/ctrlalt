#ifndef EDITOR_H
#define EDITOR_H

#include  <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <vector>

#include "Editor_Includes.h"
#include "EditorWindow.h"
#include "../ECS/ECS.h"

namespace Editor {

	class Editor {

	private:

		// bools
		bool isPromptedToExit{ false };
		bool isCreateEntity{ false };

		GLFWwindow* window;

		std::vector<EditorWindow*> gui_windows_list;
		ECS::Registry* registry;

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

		void Initialize(GLFWwindow*, ECS::Registry*);
		void Update();
		void Draw();
		void Destroy();

		// TEST FUNCTIONS
		void LoadScene(int);
		void ConsoleAddLine(std::string const&) const;
		void ConsoleClear() const;
		std::string ReadFPS() const;

		// Get bools
		bool GetExitPrompt();

	};

	Editor const* GetEditor();

}


// GLOBAL TEST FUNCTIONS





#endif