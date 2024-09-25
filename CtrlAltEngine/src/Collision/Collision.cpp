/*
@group	CTRL ALT
@file	Collision.cpp
@brief	Collision Functions to check if objects collide.
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/

#include "../Math/MathLib.h"
#include "Collision.h"

#include <algorithm>
#include <iostream>

namespace Collision
{

	// LINE


	Line::Line(MathLib::vec2 _p0, MathLib::vec2 _p1)
	{
		p0 = _p0;
		p1 = _p1;
	}

	Line::Line(Line& rhs)
	{
		p0 = rhs.p0;
		p1 = rhs.p1;
		normal = rhs.normal;
	}
	Line& Line::operator=(Line& rhs)
	{
		Line tmp{ rhs };
		swap(*this, rhs);

		return *this;
	}

	void Line::swap(Line& lhs, Line& rhs)
	{
		lhs.p0.swap(rhs.p0);
		lhs.p1.swap(rhs.p1);
		lhs.normal.swap(rhs.normal);
	}

	// CIRCLE

	Circle::Circle(MathLib::vec2 inv, float rad)
	{
		centre = inv;
		radius = rad;
	}

	Circle::Circle(Circle& rhs)
	{
		this->centre = rhs.centre;
		this->radius = rhs.radius;
	}
	Circle& Circle::operator=(Circle& rhs)
	{
		Circle tmp{ rhs };
		swap(*this, tmp);

		return *this;
	}

	void Circle::swap(Circle&lhs, Circle&rhs)
	{
		lhs.centre.swap(rhs.centre);
		std::swap(lhs.radius, rhs.radius);
	}



	bool GridCollision(MathLib::vec2& lhs, MathLib::vec2& rhs)
	{
		if (lhs.X() == rhs.X() && lhs.Y() == rhs.Y())
			return true;

		return false;
	}

	bool GridCollision(MathLib::vec3& lhs, MathLib::vec3& rhs)
	{
		if (lhs.X() == rhs.X() && lhs.Y() == rhs.Y() )
			return true;

		return false;
	}


	//AABB collision


	bool CollisionIntersection_RectRect(const MathLib::vec2& pos1,	//Input position 1
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
			float dLast =0;

			// relative vel, aabb1 is stationary, aabb2 is moving
			MathLib::vec2 Vb{};
			Vb.X(vel2.X() - vel1.X());
			Vb.Y(vel2.Y() - vel1.Y());

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



			if (Vb.y < 0)
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

	//int CheckMovingCircleToLineEdge(bool withinBothLines,
	//	const Circle& circle,
	//	const MathLib::vec2& ptEnd,
	//	const Line& lineSeg,
	//	MathLib::vec2& interPt,
	//	MathLib::vec2& normalAtCollision,
	//	float& interTime)
	//{

	//}

	//int CollisionIntersection_CircleLineSegment(const Circle& circle,
	//	const MathLib::vec2& ptEnd,
	//	const Line& lineSeg,
	//	MathLib::vec2& interPt,
	//	MathLib::vec2& normalAtCollision,
	//	float& interTime,
	//	bool& checkLineEdges)
	//{

	//}
}