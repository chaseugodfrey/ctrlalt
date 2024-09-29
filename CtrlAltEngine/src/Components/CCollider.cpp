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
		this->normal = normal;
	}

	Circle::Circle(MathLib::vec2 centre, float radius)
	{
		this->centre = centre;
		this->radius = radius;
	}
	
	AABB::AABB(MathLib::vec2 min, MathLib::vec2 max)
	{
		this->min = min;
		this->max = max;
	}
}