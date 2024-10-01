/*
@group	CTRL ALT
@file	SPhysics.cpp
@brief	Physics of the game.
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/

#include "SPhysics.h"
#include "../Components/CTransform.h"
#include "../Components/CRigidBody.h"
#include "../Math/MathLib.h"
#include "../PhysicsManager/PhysicsManager.h"
#include "../Render/glhelper.h"



namespace System
{
	

	SPhysics::SPhysics()
	{
		RequireComponent<Component::CTransform>();
		RequireComponent<Component::CRigidBody>();
	}

	void SPhysics::Update()
	{
		for (auto entity : GetEntities())
		{
			auto& transform = entity.GetComponent<Component::CTransform>();
			const auto rigidBody = entity.GetComponent<Component::CRigidBody>();

			/*transform.position.X() += rigidBody.vel.X();
			transform.position.Y() += rigidBody.vel.Y();*/
			MathLib::vec2 end = transform.position *1.5;
			MathLib::vec2 time{ 1,1 };

			PhysicsManager::Move_over_time(transform.position,end , time);

			Logger::LogInfo("ENTITY: " + std::to_string(entity.GetID()) + " POS: (" + std::to_string((int)transform.position.X()) + ", " + std::to_string((int)transform.position.Y()) + ')');
			//std::cout << transform.position << std::endl;
		}
	}

}