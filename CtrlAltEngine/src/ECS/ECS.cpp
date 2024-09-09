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

		entityId = numEntities++;
		Entity entity(static_cast<int>(entityId));

		entitiesAddQueue.insert(entity);

		if (entityId >= entityComponentMasks.size())
		{
			entityComponentMasks.resize(entityId + 1);
		}

		if (entityId >= MAX_ENTITIES)
		{
			spdlog::error("Max entities reached!");
			return Entity(-1);
		}

		// Create check for debug
		// if debug == true
		spdlog::info("Entity created with ID: {}", entityId);
		return entity;
	}

	void Registry::AddEntityToSystems(Entity entity)
	{
		const auto entityID = entity.GetID();
	
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

	void Registry::Update()
	{
		for (auto entity : entitiesAddQueue)
		{
			AddEntityToSystems(entity);
		}
		entitiesAddQueue.clear();
	}
}