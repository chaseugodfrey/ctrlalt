/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Engine.h
\author 	Michael Lazaroo
\par    	m.lazaroo@digipen.edu
\date   	Sep 08, 2024
\brief

This file contains the implementation and interface of the ECS 
(Entity Component System) architecture. The ECS is a design pattern
that allows for the separation of data and logic in a game engine.
They are seperated by components, entities, and systems.

Components are just pure data,
Entities are just IDs,
Systems are logics that operate on entities with specific components.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "ECS.h"

namespace ECS
{

	ComponentID InterfaceComponent::componentID = 0;

	///Entity Implementation
	///=========================================================================================================

	///System Implementation
	///=========================================================================================================


	/**
	 * \brief
	 * Adds an entity to the system
	 * \param entity
	 * \return void
	 * \details
	 * Adds an entity to the system
	 */
	void System::AddEntity(Entity entity) {
		entities.push_back(entity);
	}

	/**
	 * \brief
	 * Removes an entity from the system
	 * \param entity
	 * \return void
	 * \details
	 * Removes an entity from the system using erase remove idiom
	 */
	void System::RemoveEntity(Entity entity) {
		entities.erase(std::remove_if
		(entities.begin(),
			entities.end(),
			[&](Entity e) { return e == entity; }),
			entities.end());
	}
	 /**
	  * \brief
	  * Clears the entities from the system
	  * \return void
	  */
	void System::ClearEntities()
	{
		entities.clear();
	}

	/**
	 * \brief
	 * Returns the entities in the system
	 * \param 
	 * \return std::vector<Entity>
	 * \details
	 * Returns the entities in the system
	 * 
	 */
	std::vector<Entity> System::GetEntities() const {
		return entities;
	}

	/**
	 * 
	 * \brief
	 * Returns the component mask of the system
	 * \param
	 * \return const ComponentMask&
	 * \details
	 * Returns the component mask of the system,
	 * which is used to determine if an entity can be added to the system
	 */
	const ComponentMask& System::GetComponentMask() const {
		return componentMask;
	}

	///Component Implementation
	///=========================================================================================================


	///Registry Implementation
	///=========================================================================================================
	/**
	 * @brief Creates a new entity in the Entity Component System (ECS).
	 * 
	 * @details This function is responsible for creating and initializing a new entity.
	 * It performs the following steps:
	 * 1. Attempts to reuse an ID from the pool of free IDs.
	 * 2. If no free IDs are available, it increments the total entity count.
	 * 3. Resizes the component mask vector if necessary to accommodate the new entity.
	 * 4. Initializes a new Entity object with the assigned ID.
	 * 5. Adds the new entity to the addition queue for processing in the next update cycle.
	 * 
	 * @note This function does not immediately add the entity to systems. The actual
	 * system integration occurs during the next call to Update().
	 * 
	 * @see Update(), KillEntity()
	 * 
	 * @return Entity A newly created Entity object with a unique ID.
	 */
	Entity Registry::CreateEntity()
	{
		EntityID entityId;

		if (freeIDs.empty())
		{
			entityId = numEntities++;
			Logger::LogInfo("Num entities: " + std::to_string(numEntities));
			if (entityId >= entityComponentMasks.size())
			{
				entityComponentMasks.resize(entityId + 1);
			}
		}
		else
		{
			entityId = freeIDs.front();
			freeIDs.pop_front();
		}

		Entity entity(static_cast<int>(entityId));
		entity.registry = this;
		//std::string message{ "Entity created with ID: " + std::to_string(entityId) };
		//Logger::LogInfo(message);
		entitiesAddQueue.insert(entity);

		return entity;
	}

	/**
	 * @brief Marks an entity for removal from the ECS.
	 * 
	 * @details This function initiates the entity removal process by:
	 * 1. Adding the specified entity to the removal queue.
	 * 2. Logging the removal action for debugging purposes.
	 * 
	 * The entity is not immediately removed from systems or component pools.
	 * Instead, it's queued for removal, which will be processed during the next
	 * call to Update().
	 * 
	 * @note Calling this function does not immediately invalidate the entity or
	 * its components. They remain accessible until the next update cycle.
	 * 
	 * @param entity The Entity object to be marked for removal.
	 * 
	 * @see Update(), CreateEntity()
	 */
	void Registry::KillEntity(Entity entity)
	{
		entitiesRemoveQueue.insert(entity);
		Logger::LogInfo("Entity " + std::to_string(entity.GetID()) + " was ");
	}

	/**
	 * @brief Performs a complete reset of the ECS through the registry. All
	 * entities synthesized will be culled and removed.
	 * 
	 * @details This function adds a new system to the ECS registry. The system is
	 * stored in a map using its type as the key. The system is also initialized with
	 * a reference to the ECS registry.
	 * 
	 * @note Calling this function will overwrite the system completely remove entities
	 * it's associated component signature masks.
	 * 
	 * @param 
	 */
	void Registry::ClearEntities()
	{

		componentPools.clear();

		for (auto& system : systems)
		{
			system.second->ClearEntities();
		}
		
		entitiesAddQueue.clear();
		entitiesRemoveQueue.clear();
		entityComponentMasks.clear();
		numEntities = 0;
	}

	/**
	 * @brief Registers a new entity to the ECS current system.
	 * 
	 * @details This function does the following operations:
	 * 1. Retrieves the component's ID and component mask.
	 * 2. Iterates through all the systems
	 * 3. Checks within each component mask of the entity
	 * and checks with the system's component mask
	 * 4. If the entity meets the requirement's, it's added to the system.
	 * 
	 * This process is integral to the ECS' architecture as it allows for
	 * dynamic system integration based on the entity's component signature.
	 * 
	 * @param entity The entity to be registered to the ECS.
	 * 
	 * @see RemoveEntityFromSystems()
	 */
	void Registry::AddEntityToSystems(Entity entity)
	{
		const auto entityID = entity.GetID();
		Logger::LogInfo("Created Entity of " + std::to_string(entityID));
	
		const auto entityComponentMask = entityComponentMasks[entityID];

		for (auto& system : systems)
		{
			const auto& systemComponentMask = system.second->System::GetComponentMask();
			bool fitsRequirements = (entityComponentMask & systemComponentMask) == systemComponentMask;
			if (fitsRequirements)
			{
				system.second->AddEntity(entity);
			}
		}
	}	

	/**
	 * @brief
	 * Removes an entity from all systems in the ECS.
	 * 
	 * @details 
	 * Iterates through all the systems and removes the specified entity. This is 
	 * integral to entity removal or when an entity potentially has it's component
	 * signature changed drastically.
	 * 
	 * @note
	 * This function does not remove the entity from the ECS. The function still has
	 * the entity's component signature in the entityComponentMasks vector.
	 * 
	 * @see RemoveEntity()
	 */
	void Registry::RemoveEntityFromSystems(Entity entity)
	{
		for (auto& system : systems)
		{
			system.second->RemoveEntity(entity);
		}
	}

	/**
	 * @brief
	 * Updates the ECS registry
	 * 
	 * @details
	 * This function does:
	 * 1. Goes through the entities in the add queue and adds them to the systems
	 * 2. Clears the add queue
	 * 3. Goes through the entities in the remove queue and removes them from the systems
	 * 4. Clears the entities in the remove queue
	 * 
	 * @note 
	 * This function is called every frame to update the ECS registry.
	 * This function will RESET the component mask of an entity but not remove it from the ECS.
	 * 
	 * @see AddEntityToSystems(), RemoveEntityFromSystems()
	 */
	void Registry::Update()
	{
		for (auto entity : entitiesAddQueue)
		{
			AddEntityToSystems(entity);
		}
		entitiesAddQueue.clear();

		for (auto entity : entitiesRemoveQueue)
		{
			RemoveEntityFromSystems(entity);
			entityComponentMasks[entity.GetID()].reset();

			freeIDs.push_back(entity.GetID());
		}
		entitiesRemoveQueue.clear();
	}
}

