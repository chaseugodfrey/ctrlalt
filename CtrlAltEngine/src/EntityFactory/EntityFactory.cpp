/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Engine.h
\author 	Michael Lazaroo
\par    	m.lazaroo@digipen.edu
\date   	Sep 08, 2024
\brief

This file contains the implementation of the EntityFactory class methods. 
It defines how different types of entities (basic, player, enemy) are created 
and initialized with their respective components.


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

	/**
	 * @brief Construct a new Entity Factory:: Entity Factory object
	 * 
	 * @note 
	 * This function creates a new entity and initializes components for it
	 *  - CTransform
	 *  - CRenderable
	 * 
	 * @return ECS::Entity
	 * The newly synthesized entity
	 */
	ECS::Entity EntityFactory::CreateBasicEntity()
	{
		ECS::Entity entity = registry->CreateEntity();
		entity.AddComponent<Component::CTransform>();
		entity.AddComponent<Render::CRenderable>();
		Render::CRenderable& rComp = entity.GetComponent<Render::CRenderable>();
		rComp.SetTexture("test");
		return entity;
	}

	/**
	 * @brief Construct a new Entity Factory:: Entity Factory object
	 * 
	 * @note 
	 * This function creates a new entity and initializes components for it
	 *  - CTransform
	 *  - CRigidBody
	 * - CIdentifier
	 * 
	 * @return ECS::Entity
	 * The newly synthesized entity
	 */
	ECS::Entity EntityFactory::CreatePlayerEntity()
	{
		ECS::Entity entity = registry->CreateEntity();
		entity.AddComponent<Component::CTransform>();
		entity.AddComponent<Component::CRigidBody>();
		entity.AddComponent<Component::CIdentifier>("Player");

		return entity;
	}

	/**
	 * @brief Construct a new Entity Factory:: Entity Factory object
	 * 
	 * @note 
	 * This function creates a new entity and initializes components for it
	 *  - CTransform
	 *  - CRigidBody
	 * - CIdentifier
	 * 
	 * @return ECS::Entity
	 * The newly synthesized entity
	 */
	ECS::Entity EntityFactory::CreateEnemyEntity()
	{
		ECS::Entity entity = registry->CreateEntity();
		entity.AddComponent<Component::CTransform>();
		entity.AddComponent<Component::CRigidBody>();
		entity.AddComponent<Component::CIdentifier>("Enemy");
		return entity;
	}
}