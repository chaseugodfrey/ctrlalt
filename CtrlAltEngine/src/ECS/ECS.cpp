#include "ECS.h"

namespace ECS
{

	ComponentID InterfaceComponent::componentID = 0;

	///Entity Implementation
	///=========================================================================================================

	///System Implementation
	///=========================================================================================================

	void System::AddEntity(Entity entity) {
		entities.push_back(entity);
	}

	void System::RemoveEntity(Entity entity) {
		entities.erase(std::remove_if
		(entities.begin(),
			entities.end(),
			[&](Entity e) { return e == entity; }),
			entities.end());
	}

	void System::ClearEntities()
	{
		entities.clear();
	}

	std::vector<Entity> System::GetEntities() const {
		return entities;
	}

	const ComponentMask& System::GetComponentMask() const {
		return componentMask;
	}

	///Component Implementation
	///=========================================================================================================


	///Registry Implementation
	///=========================================================================================================
	Entity Registry::CreateEntity()
	{
		EntityID entityId;

		if (freeIDs.empty())
		{
			entityId = numEntities++;
			std::cout << "Num entities: " << numEntities << std::endl;
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

	void Registry::KillEntity(Entity entity)
	{
		entitiesRemoveQueue.insert(entity);
		Logger::LogInfo("Entity " + std::to_string(entity.GetID()) + " was ");
	}

	void Registry::ClearEntities()
	{
		componentPools.clear();

		for (auto& system : systems)
		{
			system.second->ClearEntities();
		}
		
		numEntities = 0;
		std::cout << "AAAAAAAAA" << std::endl;
	}

	void Registry::AddEntityToSystems(Entity entity)
	{
		const auto entityID = entity.GetID();
		std::cout << "Created Entity of " << entityID << std::endl;
	
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

	void Registry::RemoveEntityFromSystems(Entity entity)
	{
		for (auto& system : systems)
		{
			system.second->RemoveEntity(entity);
		}
	}

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