#ifndef EDITOR_H
#define EDITOR_H

#include  <GLFW/glfw3.h>
#include "glm/glm.hpp"

namespace GameEditor {

	class Editor {

	private:

		// bools
		bool isPromptedToExit{ false };

		GLFWwindow* window;

		void DisplayMenuBar();
		void DisplayHierachy();
		void DisplayInspector();
		void DisplayScene();

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