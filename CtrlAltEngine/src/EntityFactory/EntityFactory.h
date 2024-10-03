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