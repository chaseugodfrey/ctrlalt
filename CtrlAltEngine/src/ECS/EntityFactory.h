#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "ECS.h"
#include "../Components/CRigidBody.h"
#include "../Components/CTransform.h"
#include "../Scene/SceneManager.h"
#include "../Logger/Logger.h"

namespace ECS
{
	class EntityFactory
	{
	private:
		Registry* registry;
		Scene::SceneManager* sceneManager;
	public:
		EntityFactory(Registry* reg, Scene::SceneManager* sm) : registry(reg), sceneManager(sm) {}

		Entity CreateBasicEntity()
		{
			Entity entity = registry->CreateEntity();
			entity.AddComponent<Component::CTransform>();
		}

		Entity CreatePlayerEntity()
		{
			Entity entity = registry->CreateEntity();
			entity.AddComponent<Component::CTransform>();
			entity.AddComponent<Component::CRigidBody>();
			entity.AddComponent<Component::CIdentifier>("Player");
		}
		
		Entity CreateEnemyEntity()
		{
			Entity entity = registry->CreateEntity();
			entity.AddComponent<Component::CTransform>();
			entity.AddComponent<Component::CRigidBody>();
			entity.AddComponent<Component::CIdentifier>("Enemy");
		}
	};
}


#endif
