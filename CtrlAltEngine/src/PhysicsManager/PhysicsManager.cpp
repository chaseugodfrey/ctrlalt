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
	float g_dt = 0.001f;

	void Move_over_time(MathLib::vec2& start, MathLib::vec2& end, MathLib::vec2& time)
	{
		if (start.x != end.x && start.y != end.y)
		{
			MathLib::vec2 dist = end - start;
			float y_speed = dist.y / time.y;
			float x_speed = dist.x / time.x;

			start.x += x_speed * g_dt;
			start.y += y_speed * g_dt;

			time.x -= g_dt;
			time.y-= g_dt;
		}
	}

	void Move_Basic(MathLib::vec2& start, MathLib::vec2& end, const MathLib::vec2& velocity)
	{
		//if (start.x != end.x && start.y != end.y)
		//{
			start.x += velocity.x * g_dt;
			start.y += velocity.y * g_dt;
		//}
	}
}

