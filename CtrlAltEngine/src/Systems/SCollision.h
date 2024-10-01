/*
@group	CTRL ALT
@file	SCollision.h
@brief	Collision Functions to check if objects collide.
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/
#ifndef SCOLLISION_H
#define SCOLLISION_H

#include <iostream>
#include "../ECS/ECS.h"
#include "../Math/MathLib.h"
#include "../Components/CCollider.h"

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


		bool GridCollision( MathLib::vec2& lhs,  MathLib::vec2& rhs);


		bool GridCollision( MathLib::vec3& lhs,  MathLib::vec3& rhs);

		bool CollisionIntersection_RectRect(const MathLib::vec2& pos1,	//Input position 1
											const float w1,				//Input width
											const float h1,				//Input height
											const MathLib::vec2& vel1,  //Input velocity
											const MathLib::vec2& pos2,	//Input position 2
											const float w2,				//Input width
											const float h2,				//Input height
											const MathLib::vec2& vel2,	//Input velocity
											float& firstTimeOfCollision);

		bool CollisionIntersection_CircleLineSegment(const Component::Circle& circle,			//Circle data - input
													const MathLib::vec2& ptEnd,					//End circle position - input
													const Component::Line& lineSeg,				//Line segment - input
													MathLib::vec2& interPt,						//Intersection point - output
													MathLib::vec2& normalAtCollision,			//Normal vector at collision time - output
													float& interTime);							//Intersection time ti - output						
	};

}

#endif