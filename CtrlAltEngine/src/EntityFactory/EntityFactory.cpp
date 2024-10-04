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