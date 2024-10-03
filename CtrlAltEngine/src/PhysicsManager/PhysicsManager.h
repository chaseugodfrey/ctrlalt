/*
@group	CTRL ALT
@file	PhysicsManager.h
@brief	Physics of the game.
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/
#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "../Systems/SPhysics.h"
#include "../Math/MathLib.h"


namespace PhysicsManager
{
	/******************************************************************************/
	/*
		Moves the starting point to the end point over time specified.
	*/
	/******************************************************************************/
	void Move_over_time(MathLib::vec2& start, MathLib::vec2& end, MathLib::vec2& time);

	/******************************************************************************/
	/*
		Moves the starting point to the end point.
	*/
	/******************************************************************************/
	void Move_Basic(MathLib::vec2& start, MathLib::vec2& end, const MathLib::vec2& velocity);


}
	

#endif