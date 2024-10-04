/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Engine.h
\author 	Michael Lazaroo
\par    	m.lazaroo@digipen.edu
\date   	Sep 08, 2024
\brief
Added the Event class to the EventBus.h file. This is to prevent circular 
dependencies between the Event and EventBus classes.


Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef EVENT_H
#define EVENT_H
//Base class for all events that we wish to execute
namespace Event {
	class Event
	{
	public:
		Event() = default;
	};
}
#endif