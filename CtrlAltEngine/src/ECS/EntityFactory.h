#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "ECS.h"
#include "../Components/CRigidBody.h"
#include "../Components/CTransform.h"
#include "../Scene/SceneManager.h"

namespace ECS
{
	class EntityFactory
	{
	private:
		Registry* registry;
		Scene::SceneManager* sceneManager;
	public:
	};
}


#endif
