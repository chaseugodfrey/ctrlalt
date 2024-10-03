#include "EntityFactory.h"
#include "../Render/Render.h"
#include "../Components/CRigidBody.h"
#include "../Components/CTransform.h"
#include "../Components/CIdentifier.h"
#include "../Logger/Logger.h"


namespace EntityFactory {
	ECS::Entity EntityFactory::CreateBasicEntity()
	{
		ECS::Entity entity = registry->CreateEntity();
		entity.AddComponent<Component::CTransform>();
		entity.AddComponent<Render::CRenderable>();
		Render::CRenderable& rComp = entity.GetComponent<Render::CRenderable>();
		rComp.SetTexture("test");
		return entity;
	}

	ECS::Entity EntityFactory::CreatePlayerEntity()
	{
		ECS::Entity entity = registry->CreateEntity();
		entity.AddComponent<Component::CTransform>();
		entity.AddComponent<Component::CRigidBody>();
		entity.AddComponent<Component::CIdentifier>("Player");

		return entity;
	}

	ECS::Entity EntityFactory::CreateEnemyEntity()
	{
		ECS::Entity entity = registry->CreateEntity();
		entity.AddComponent<Component::CTransform>();
		entity.AddComponent<Component::CRigidBody>();
		entity.AddComponent<Component::CIdentifier>("Enemy");
		return entity;
	}
}