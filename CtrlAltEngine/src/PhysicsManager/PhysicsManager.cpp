/*
@group	CTRL ALT
@file	PhysicsManager.cpp
@brief	Physics of the game.
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/

#include "PhysicsManager.h"
#include "../Render/glhelper.h"



namespace PhysicsManager
{
	//float g_dt = GLHelper::delta_time;
	float g_dt = 0.001;

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

