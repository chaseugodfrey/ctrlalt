#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "../ECS/ECS.h"
#include "../Components/CRigidBody.h"
#include "../Components/CTransform.h"
#include "../Components/CIdentifier.h"
#include "../Logger/Logger.h"

namespace EntityFactory
{
	class EntityFactory
	{
	private:
		ECS::Registry * registry;
	public:
		EntityFactory(ECS::Registry* reg) : registry(reg) {}
		ECS::Entity CreateBasicEntity()
		{
			ECS::Entity entity = registry->CreateEntity();
			entity.AddComponent<Component::CTransform>();
			return entity;
		}

		ECS::Entity CreatePlayerEntity()
		{
			ECS::Entity entity = registry->CreateEntity();
			entity.AddComponent<Component::CTransform>();
			entity.AddComponent<Component::CRigidBody>();
			entity.AddComponent<Component::CIdentifier>("Player");
			
			return entity;
		}
		
		ECS::Entity CreateEnemyEntity()
		{
			ECS::Entity entity = registry->CreateEntity();
			entity.AddComponent<Component::CTransform>();
			entity.AddComponent<Component::CRigidBody>();
			entity.AddComponent<Component::CIdentifier>("Enemy");
			return entity;
		}
	};
}

#endif