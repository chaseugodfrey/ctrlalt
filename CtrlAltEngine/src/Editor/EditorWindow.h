#ifndef EDITOR_WINDOW_H
#define EDITOR_WINDOW_H


#include "Editor_Includes.h"
#include <string>

namespace Editor
{
	class EditorWindow
	{
	public:

		std::string label;

		virtual void Display() = 0;

		virtual ~EditorWindow() = default;
	};
}

#endif