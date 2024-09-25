/*
@group	CTRL ALT
@file	Physics.h
@brief	Physics of the game.
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/
#ifndef PHYSICS_H
#define PHYSICS_H

#include "../Math/MathLib.h"

namespace Physics
{
	extern float g_dt;

	/******************************************************************************/
	/*
		Update loop for Physics
	 */
	 /******************************************************************************/
	void Update();

	/******************************************************************************/
	/*
		Moves the starting point to the end point over time specified.
	 */
	 /******************************************************************************/
	void Move_over_time(MathLib::vec2& start, MathLib::vec2& end, MathLib::vec2& time);



}



#endif
