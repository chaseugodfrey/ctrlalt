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