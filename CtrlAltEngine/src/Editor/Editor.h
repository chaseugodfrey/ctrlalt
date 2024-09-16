#ifndef EDITOR_H
#define EDITOR_H

#include  <GLFW/glfw3.h>
#include "glm/glm.hpp"

namespace GameEditor
{
	class Editor
	{

	private:

		// bools
		bool isRunning{ true };
		bool isPromptedToExit{ false };

		
		GLFWwindow* window;

		void DisplayMenuBar();
		void DisplayHierachy();
		void DisplayInspector();
		void DisplayScene();

		// Constructor
		// Requires window to be referenced for creation of editor for imgui purposes
		// Deleted Constructors


	public:
		Editor();
		~Editor();

		void Load(GLFWwindow* _window);
		void Initialize();
		void Update();
		void Render();
		void Destroy();

		// Get bools
		bool GetExitPrompt();
	};

	static Editor editor;

	void Activate(GLFWwindow* _window);
	void Run();
	void Terminate();
	bool GetExitPrompt();

}



#endif