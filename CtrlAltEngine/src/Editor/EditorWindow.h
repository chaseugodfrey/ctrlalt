#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H



#include "Editor_Includes.h"
#include <string>

namespace GameEditor
{
	class EditorWindow
	{
	public:

		std::string label;

		virtual void Display() = 0;

		virtual ~EditorWindow() = default;
	};
}
#endif // !