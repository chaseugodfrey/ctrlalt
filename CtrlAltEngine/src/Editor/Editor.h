/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Editor.h
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Sep 08, 2024
\brief

ImGui Editor Interface to wrap engine functionality and display necessary information
for editing scenes.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef EDITOR_H
#define EDITOR_H

/**
GLFW_INCLUDE_NONE makes the GLFW header not include any OpenGL or OpenGL ES API header. This is useful in combination with an extension loading library.

If none of the above inclusion macros are defined, the standard OpenGL GL/gl.h header (OpenGL/gl.h on macOS) is included, unless GLFW detects the inclusion guards of any OpenGL, OpenGL ES or extension loader header it knows about.

The following macros control the inclusion of additional API headers. Any number of these may be defined simultaneously, and/or together with one of the above macros.
*/
#define GLFW_INCLUDE_NONE

#include  <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <vector>
#include <memory>

// Include Editor 
#include "EditorIncludes.h"
#include "EditorContext.h"
#include "EditorService.h"

#include "Windows/EditorBaseWindow.h"
#include "EditorAllWindows.h"

#include "../Scene/SceneManager.h"
#include "../ECS/ECS.h"
#include "../Debug/Debugger.h"

namespace CtrlAltEditor {

	class Editor {

	private:

		std::unique_ptr<EditorContext> context;
		std::unique_ptr<EditorService> service;

		// bools
		bool isPromptedToExit{ false };
		bool isCreateEntity{ false };

		// TEST FUNCTIONS

	public:
		Editor();
		~Editor();

		void Setup(GLFWwindow*, Scene::SceneManager&, Debug::FrameTimer&);
		void Initialize(GLuint);
		void Update();
		void Render(GLFWwindow*);
		void Destroy();

		void DisplayGUIWindows();

		// TEST FUNCTIONS
		void LoadScene(int);

		// Get bools
		bool GetExitPrompt();

	};

}


// GLOBAL TEST FUNCTIONS





#endif