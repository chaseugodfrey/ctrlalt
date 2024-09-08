#include "ECS.h"

namespace ECS
{
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

	const ComponentSignature& System::GetSignature() const {
		return componentSignature;
	}

	///Component Implementation
	///=========================================================================================================
	

}