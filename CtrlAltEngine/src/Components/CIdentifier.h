#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>

namespace Component
{
	struct CIdentifier
	{
		std::string name;
		CIdentifier(std::string name = "") : name(name) {};
	};
}

#endif