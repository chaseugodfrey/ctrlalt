#include "EditorContext.h"

namespace CtrlAltEditor
{
	EditorContext::~EditorContext() {}
	std::unique_ptr<EditorWindow> EditorContext::GetWindow(int) const
	{
		return std::unique_ptr<EditorWindow>();
	}
}