/*
@group	CTRL ALT
@file	SCollsion.cpp
@brief	Collsion of the game.
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/

#include "SCollision.h"
#include "../ECS/ECS.h"
#include "../Components/CTransform.h"
#include "../Components/CRigidBody.h"
#include "../Components/CCollider.h"

namespace System
{
	SCollision::SCollision()
	{
		RequireComponent<Component::CTransform>();
		RequireComponent<Component::CRigidBody>();
		RequireComponent<Component::AABB>();
		RequireComponent<Component::Circle>();
		RequireComponent<Component::Line>();
	}

	void SCollision::Update()
	{
		for (auto entity : GetEntities())
		{
			auto& transform = entity.GetComponent<Component::CTransform>();
			const auto rigidBody = entity.GetComponent<Component::CRigidBody>();
			const auto aabb = entity.GetComponent<Component::AABB>();

			bool grid_collided = false;

			for (auto entity2 : GetEntities())
			{
				auto& transform2 = entity2.GetComponent<Component::CTransform>();
				if (entity == entity2)
				{
					continue;
				}

				grid_collided = SCollision::GridCollision(transform.position, transform2.position);
			}

			//Logger::LogInfo("ENTITY: " + std::to_string(entity.GetID()) + " POS: (" + std::to_string((int)transform.position.X()) + ", " + std::to_string((int)transform.position.Y()) + ')');
			//std::cout << transform.position << std::endl;
		}
	}

	bool SCollision::GridCollision(MathLib::vec2& lhs, MathLib::vec2& rhs)
	{
		if (lhs == rhs)
			return true;

		return false;
	}

	bool SCollision::GridCollision(MathLib::vec3& lhs, MathLib::vec3& rhs)
	{
		if (lhs == rhs)
			return true;

		return false;
	}

	//AABB collision

	bool SCollision::CollisionIntersection_RectRect(const MathLib::vec2& pos1,	//Input position 1
													const float w1,				//Input width
													const float h1,				//Input height
													const MathLib::vec2& vel1,  //Input velocity
													const MathLib::vec2& pos2,	//Input position 2
													const float w2,				//Input width
													const float h2,				//Input height
													const MathLib::vec2& vel2,	//Input velocity
													float& firstTimeOfCollision) //Output: the calculated value of tFirst, below, must be returned here
	{

		float aabb1_min_x = pos1.X() - w1 / 2;
		float aabb1_min_y = pos1.Y() - h1 / 2;

		float aabb1_max_x = pos1.X() + w1 / 2;
		float aabb1_max_y = pos1.Y() + h1 / 2;

		float aabb2_min_x = pos2.X() - w2 / 2;
		float aabb2_min_y = pos2.Y() - h2 / 2;

		float aabb2_max_x = pos2.X() + w2 / 2;
		float aabb2_max_y = pos2.Y() + h2 / 2;

		if ((aabb2_min_y < aabb1_max_y && aabb2_min_x < aabb1_max_x) && (aabb1_min_y < aabb2_max_y && aabb1_min_x < aabb2_max_x))
		{
			return true;
		}
		else
		{
			firstTimeOfCollision = 0;
			float dLast = 0;

			// relative vel, aabb1 is stationary, aabb2 is moving
			MathLib::vec2 Vb{};
			Vb.X() = vel2.X() - vel1.X();
			Vb.Y() = vel2.Y() - vel1.Y();

			if (Vb.X() < 0)
			{
				if (aabb1_min_x > aabb2_max_x)
				{
					return false;
				}
				if (aabb1_max_x < aabb2_min_x)
				{
					firstTimeOfCollision = std::max((aabb2_min_x - aabb1_max_x) / Vb.X(), firstTimeOfCollision);
				}
				if (aabb1_min_x < aabb2_max_x)
				{
					dLast = std::min((aabb2_max_x - aabb1_min_x) / Vb.X(), dLast);
				}
			}

			else if (Vb.X() > 0)
			{
				if (aabb1_max_x < aabb2_min_x)
				{
					return false;
				}
				if (aabb1_min_x > aabb2_max_x)
				{
					firstTimeOfCollision = std::max((aabb1_min_x - aabb2_max_x) / Vb.X(), firstTimeOfCollision);
				}
				if (aabb1_max_x > aabb2_min_x)
				{
					dLast = std::min((aabb1_max_x - aabb2_min_x) / Vb.X(), dLast);
				}
			}

			else
			{
				if (aabb1_max_x < aabb2_min_x)
				{
					return false;
				}
				if (aabb1_min_x > aabb2_max_x)
				{
					return false;
				}
			}

			if (firstTimeOfCollision > dLast)
			{
				return false;
			}



			if (Vb.Y() < 0)
			{
				if (aabb1_min_y > aabb2_max_y)
				{
					return false;
				}
				if (aabb1_max_y < aabb2_min_y)
				{
					firstTimeOfCollision = std::max((aabb2_min_y - aabb1_max_y) / Vb.Y(), firstTimeOfCollision);
				}
				if (aabb1_min_y < aabb2_max_y)
				{
					dLast = std::min((aabb2_max_y - aabb1_min_y) / Vb.Y(), dLast);
				}
			}

			else if (Vb.Y() > 0)
			{
				if (aabb1_max_y < aabb2_min_y)
				{
					return false;
				}
				if (aabb1_min_y > aabb2_max_y)
				{
					firstTimeOfCollision = std::max((aabb1_min_y - aabb2_max_y) / Vb.Y(), firstTimeOfCollision);
				}
				if (aabb1_max_y > aabb2_min_y)
				{
					dLast = std::min((aabb1_max_y - aabb2_min_y) / Vb.Y(), dLast);
				}
			}

			else
			{
				if (aabb1_max_y < aabb2_min_y)
				{
					return false;
				}
				if (aabb1_min_y > aabb2_max_y)
				{
					return false;
				}
			}

			if (firstTimeOfCollision > dLast)
			{
				return false;
			}
		}
		return true;
	}

	bool SCollision::CollisionIntersection_CircleLineSegment(const Component::Circle& circle,			//Circle data - input
												const MathLib::vec2& ptEnd,					//End circle position - input
												const Component::Line& lineSeg,				//Line segment - input
												MathLib::vec2& interPt,						//Intersection point - output
												MathLib::vec2& normalAtCollision,			//Normal vector at collision time - output
												float& interTime)
	{
		//N^
		MathLib::vec2 normalizedNormal = lineSeg.normal;
		normalizedNormal.normalise();

		MathLib::vec2 P0 = lineSeg.p0;
		MathLib::vec2 P1 = lineSeg.p1;
		MathLib::vec2 Bs = circle.centre;
		MathLib::vec2 Be = ptEnd;
		MathLib::vec2 V = Be - Bs;
		MathLib::vec2 M{};
		M.X() = V.Y();
		M.Y() = -V.X();

		//N^.Bs
		float startingPointCircle = normalizedNormal*Bs;

		//N^.P0
		float startingPointLine = normalizedNormal* P0;

		//N^.Bs - N^.P0 <= -R
		if (startingPointCircle - startingPointLine <= -circle.radius) /// weird not -R
		{
			//P0 - R*N^
			MathLib::vec2 P0PrimeVec = P0 - (normalizedNormal * circle.radius);

			//P1 - R*N^
			MathLib::vec2 P1PrimeVec = P1 - (normalizedNormal * circle.radius);

			//BsP0'
			MathLib::vec2 BsP0Prime = P0PrimeVec - Bs;

			//BsP1'
			MathLib::vec2 BsP1Prime = P1PrimeVec - Bs;

			//M.BsP0'
			float normalPoint0 = M * BsP0Prime;

			//M.BsP1'
			float normalPoint1 = M * BsP1Prime;

			//N^.V
			float normalBVector = normalizedNormal * V;

			//M.BsP0' * M.BsP1' < 0
			if (normalPoint0 * normalPoint1 < 0)
			{
				//(N^.P0 - N^.Bs - R)/(N^.V)
				float Ti = (startingPointLine - startingPointCircle - circle.radius) / (normalBVector);
				if (Ti >= 0 && Ti <= 1)
				{
					//V*Ti
					MathLib::vec2 VScaleTi = normalizedNormal * Ti;

					//Bi = Bs + V*Ti
					MathLib::vec2 Bi = Bs + VScaleTi;

					//Apply reflection

					interTime = Ti;
					interPt = Bi;
					normalAtCollision = -normalizedNormal;
					return true;
				}
			}
		}
		//N^.Bs - N^.P0 >= R
		else if (startingPointCircle - startingPointLine >= circle.radius)
		{
			//P0 + R*N^
			MathLib::vec2 P0PrimeVec = P0 + (normalizedNormal * circle.radius);

			//P1 + R*N^
			MathLib::vec2 P1PrimeVec = P1 + (normalizedNormal * circle.radius);

			//BsP0'
			MathLib::vec2 BsP0Prime = P0PrimeVec - Bs;

			//BsP1'
			MathLib::vec2 BsP1Prime = P1PrimeVec - Bs;

			//M.BsP0'
			float normalPoint0 = M * BsP0Prime;

			//M.BsP1'
			float normalPoint1 = M * BsP1Prime;

			//N^.V
			float normalBVector = normalizedNormal * V;

			//M.BsP0' * M.BsP1' < 0
			if (normalPoint0 * normalPoint1 < 0)
			{
				//N^.P0 - N^.Bs + R/(N^.V)
				float Ti = (startingPointLine - startingPointCircle + circle.radius) / (normalBVector);

				if (Ti >= 0 && Ti <= 1)
				{
					//V*Ti
					MathLib::vec2 VScaleTi = normalizedNormal * Ti;

					//Bi = Bs + V*Ti
					MathLib::vec2 Bi = Bs + VScaleTi;

					//BiBe
					MathLib::vec2 BiBeVector = Be - Bi;

					//Be' = Applyreflection(-N^,BiBe)

					interTime = Ti;
					interPt = Bi;
					normalAtCollision = normalizedNormal;
					return true;
				}
			}

		}
		
		return false; // no intersection
	}
}