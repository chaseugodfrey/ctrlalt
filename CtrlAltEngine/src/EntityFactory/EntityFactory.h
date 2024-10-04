/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Engine.h
\author 	Michael Lazaroo
\par    	m.lazaroo@digipen.edu
\date   	Sep 08, 2024
\brief

This file contains the declaration of the EntityFactory class methods. 
It defines how different types of entities (basic, player, enemy) are created 
and initialized with their respective components.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "../ECS/ECS.h"


namespace EntityFactory
{
	/**
	 * @brief Construct a new Entity Factory:: Entity Factory object
	 * 
	 * @note
	 * Takes in the ECS system registry, so entities are synthesized within the
	 * current running registry.
	 */
	class EntityFactory
	{
	private:
		ECS::Registry * registry;
	public:
		EntityFactory(ECS::Registry* reg) : registry(reg) {}
		ECS::Entity CreateBasicEntity();

		ECS::Entity CreatePlayerEntity();
		
		ECS::Entity CreateEnemyEntity();
	};
}

#endif