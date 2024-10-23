#ifndef IDENTIFIER_H
#define IDENTIFIER_H
#include "../src/pch.h" 
#include <string>

namespace Component
{
	struct CIdentifier
	{
		std::string name;
		CIdentifier(std::string name = "Entity") : name(name) {};
	};
}

#endif