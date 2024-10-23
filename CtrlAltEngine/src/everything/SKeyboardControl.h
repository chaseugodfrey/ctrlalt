/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Engine.h
\author 	Michael Lazaroo
\par    	m.lazaroo@digipen.edu
\date   	Sep 08, 2024
\brief


Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "../src/pch.h"
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