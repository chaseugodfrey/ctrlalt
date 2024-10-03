/*
@group	CTRL ALT
@file	CCollider.cpp
@brief	Collision Functions to check if objects collide.
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/

#include "CCollider.h"

namespace Component
{
	Line::Line(MathLib::vec2 p0, MathLib::vec2 p1, MathLib::vec2 normal)
	{
		this->p0 = p0;
		this->p1 = p1;
		if (normal == MathLib::vec2{})
		{
			this->normal.X() = p1.Y() - p0.Y();
			this->normal.Y() = p0.X() - p1.X();
		}
		else
		{
			this->normal = normal;
		}
	}

	Circle::Circle(MathLib::vec2 centre, float radius)
	{
		this->centre = centre;
		this->radius = radius;
	}
	
	AABB::AABB(MathLib::vec2 pos, float width, float height)
	{
		float half_width = width / 2;
		float half_height = height / 2;

		min = MathLib::vec2(pos.X() - half_width, pos.Y() - half_height);
		max = MathLib::vec2(pos.X() + half_width, pos.Y() + half_height);
	}
}