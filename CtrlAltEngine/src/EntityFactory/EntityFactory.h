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

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "../ECS/ECS.h"


namespace EntityFactory
{
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