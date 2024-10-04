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

#ifndef KEYPRESSEVENT_H
#define KEYPRESSEVENT_H

#include "../EventManager/Event.h"

class KeyPressEvent : public Event::Event
{
public:
	int key;
	int scancode;
	int action;
	int mods;

	KeyPressEvent(int key)
		: key(key) {};

};
#endif