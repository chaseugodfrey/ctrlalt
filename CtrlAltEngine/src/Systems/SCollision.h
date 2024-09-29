/*
@group	CTRL ALT
@file	Collision.h
@brief	Collision Functions to check if objects collide.
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/
#ifndef SCOLLISION_H
#define SCOLLISION_H

#include <iostream>
#include "../ECS/ECS.h"
#include "../Math/MathLib.h"

namespace System
{
	class SCollision : public ECS::System
	{
	public:
		/******************************************************************************/
		/*
			Constructor to have required components
		 */
		 /******************************************************************************/
		SCollision();

		/******************************************************************************/
		/*
			Update loop for Collision
		 */
		 /******************************************************************************/
		void Update();


		bool GridCollision(MathLib::vec2& lhs, MathLib::vec2& rhs);


		bool GridCollision(MathLib::vec3& lhs, MathLib::vec3& rhs);
	};

}

#endif