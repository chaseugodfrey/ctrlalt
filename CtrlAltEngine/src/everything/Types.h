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
	using EntityID = int;
	using NumEntities = int;
	constexpr NumEntities MAX_ENTITIES = 100'000'000;

	//Components
	using ComponentID = int; //Allows up to 256 components
	constexpr ComponentID MAX_COMPONENTS = 256;
	// Eacg bit in the mask represents a component
	// '1' == active '0' == inactive
	using ComponentMask = std::bitset <MAX_COMPONENTS>;
	using SignatureMasks = std::vector<ComponentMask>;
	class InterfaceComponent {
	protected:
		static ComponentID componentID;
	};

	//Pool
	//We need a pool of interfaces to store all the components because we don't know the type of the component at compile time.
	//This works because all components inherit from InterfaceComponent that has a static variable componentID.
	class InterfacePool {
	public:
		virtual ~InterfacePool() = default;
		virtual void RemoveEntityFromPool(int entityID) = 0;
	};

	//Systems
}


#endif