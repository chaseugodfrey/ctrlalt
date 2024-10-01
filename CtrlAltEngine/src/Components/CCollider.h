/*
@group	CTRL ALT
@file	CCollider.h
@brief	Collision Functions to check if objects collide.
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/
#ifndef CCOLLISION_H
#define CCOLLISION_H

#include <iostream>
#include "../Math/MathLib.h"

namespace Component
{
	/******************************************************************************/
	/*
		A class to represent a Line segment from 2 points.
	 */
	 /******************************************************************************/
	struct Line
	{
		MathLib::vec2 p0;
		MathLib::vec2 p1;
		MathLib::vec2 normal;

		Line(MathLib::vec2 p0 = MathLib::vec2{}, MathLib::vec2 p1 = MathLib::vec2{}, MathLib::vec2 normal = MathLib::vec2{});
	};

	/******************************************************************************/
	/*
		A class to represent a Circle with a centre and a radius.
	 */
	 /******************************************************************************/
	struct Circle
	{
		MathLib::vec2 centre;
		float radius;

		Circle(MathLib::vec2 centre = MathLib::vec2{}, float radius = 0.f);
	};

	/******************************************************************************/
	/*
		A class to represent a AABB of an object.
	 */
	 /******************************************************************************/
	struct AABB
	{
		// Bottom left point of object
		MathLib::vec2 min;

		// Top right point of object
		MathLib::vec2 max;

		AABB(MathLib::vec2 pos = MathLib::vec2{}, float width = 0.f, float height = 0.f);
	};

}

#endif

