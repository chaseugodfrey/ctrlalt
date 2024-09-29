/*
@group	CTRL ALT
@file	Physics.h
@brief	Physics of the game.
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/
#ifndef SPHYSICS_H
#define SPHYSICS_H

#include "../Components/CTransform.h"
#include "../Components/CRigidBody.h"
#include "../Math/MathLib.h"
#include "../ECS/ECS.h"

namespace System
{
	extern float g_dt;

	class SPhysics : public ECS::System
	{
	public:
		/******************************************************************************/
		/*
			Constructor to have required components
		 */
		 /******************************************************************************/
		SPhysics();

		/******************************************************************************/
		/*
			Update loop for Physics
		 */
		 /******************************************************************************/
		void Update();
	};
}



#endif

