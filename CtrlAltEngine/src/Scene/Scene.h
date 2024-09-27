#ifndef SCENE_H
#define SCENE_H

#include "../Components/CTransform.h"
#include "../Components/CRigidBody.h"
#include "../Systems/SMovement.h"
#include "../Engine/Engine.h"
#include "../ECS/ECS.h"

namespace Scene{

	class Scene {

	private:
		ECS::Registry* registry;

	public:
		Scene(ECS::Registry*);
		~Scene();

		void Init();
		void Update();

	};
}




#endif