/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Types.h
\author 	Michael Lazaroo
\par    	m.lazaroo@digipen.edu
\date   	Sep 08, 2024
\brief		


Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef TYPE_H
#define TYPE_H

#include <bitset>
#include <vector>

namespace ECS
{
	/******************************************************************************/
	/*!
	* Defines, aliases, and typedefs
	*/
	/******************************************************************************/
	//Entities
	using EntityID = uint64_t;
	using numEntities = uint32_t;
	constexpr numEntities MAX_ENTITIES = 100000;

	//Components
	using ComponentID = uint8_t; //Allows up to 256 components
	constexpr ComponentID MAX_COMPONENTS = 256;
	// Eacg bit in the mask represents a component
	// '1' == active '0' == inactive
	using Signature = std::bitset <MAX_COMPONENTS>;
	using Masks = std::vector<Signature>;
	class InterfaceComponent {
	protected:
		static ComponentID componentID;
	};

	//Pool
	//We need a pool of interfaces to store all the components because we don't know the type of the component at compile time.
	//This works because all components inherit from InterfaceComponent that has a static variable componentID.
	//This works because inheritance is a compile-time concept.
	class InterfacePool {
	public:
		virtual ~InterfacePool() = default;
	};

	//Systems
}


#endif