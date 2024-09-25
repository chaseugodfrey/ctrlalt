/*
@group	CTRL ALT
@file	Physics.cpp
@brief	Physics of the game.
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/

#include "Physics.h"


namespace Physics
{
	float g_dt = delta_time;

	void Update()
	{

	}

	void Move_over_time(MathLib::vec2& start, MathLib::vec2& end, MathLib::vec2& time)
	{
		if (start.X() != end.X() && start.Y() != end.Y())
		{
			MathLib::vec2 dist = end - start;
			float y_speed = dist.Y() / time.Y();
			float x_speed = dist.X() / time.X();

			start.X() += x_speed * g_dt;
			start.Y() += x_speed * g_dt;

			time.X() -= g_dt;
			time.Y() -= g_dt;
		}
	}



}