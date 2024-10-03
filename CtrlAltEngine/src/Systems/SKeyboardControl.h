#ifndef KEYBOARDCONTROLSYSTEM_H
#define KEYBOARDCONTROLSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventManager/EventBus.h"
#include "../Events/KeyPressEvent.h"

namespace System{
	class SKeyboardControl : public ECS::System
	{
	public:
		SKeyboardControl()
		{
		}

		void SubscribeToEvents(std::unique_ptr<Event::EventBus>& bus)
		{
			bus->SubscribeToEvent<KeyPressEvent>(this, &SKeyboardControl::OnKeyPressed);
		}
	
		void OnKeyPressed(KeyPressEvent& event)
		{
			std::string keyCode = std::to_string(event.key);
			//std::string keySymbol((size_t)1, event.key);
			Logger::LogInfo("Key Pressed: " + keyCode);

		}
	};
}
#endif