#include "EditorBaseWindow.h"

namespace CtrlAltEditor
{
	EditorWindow::EditorWindow(EditorService& _service, EditorContext const& _context) : 
		service(_service),
		context(_context) {};
}