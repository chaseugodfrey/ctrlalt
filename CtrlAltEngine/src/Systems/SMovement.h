#ifndef SMOVEMENT_H
#define SMOVEMENT_H

#include "../ECS/ECS.h"
#include "../Components/CTransform.h"
#include "../Components/CRigidBody.h"

// to disable in future (?)

namespace System {
	class SMovement : public ECS::System
	{
	public:
		SMovement()
		{
			RequireComponent<Component::CTransform>();
			RequireComponent<Component::CRigidBody>();
		}

		void Update()
		{
			for (auto entity : GetEntities())
			{
				//auto& transform = entity.GetComponent<Component::CTransform>();
				//const auto rigidBody = entity.GetComponent<Component::CRigidBody>();

				//transform.position.X() += rigidBody.vel.X();
				//transform.position.Y() += rigidBody.vel.Y();

				//Logger::LogInfo("ENTITY: " + std::to_string(entity.GetID()) + " POS: (" + std::to_string((int)transform.position.x) + ", " + std::to_string((int)transform.position.y) + ')');
			}
		}
	};
}
#endif