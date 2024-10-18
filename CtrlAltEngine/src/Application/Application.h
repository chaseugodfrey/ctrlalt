#ifndef APP_H
#define APP_H

// This is here because= GLFW uses the APIENTRY macro to declare the same name function, both have windows.h  files
#ifdef _WIN32
#include <windows.h>
#else
#define APIENTRY
#endif

namespace Application
{
	class App
	{
	private:

		bool isRunning;
		int windowWidth;
		int windowHeight;

	public:

		void Init();
		void Run();
		void Shutdown();


	};
}

#endif