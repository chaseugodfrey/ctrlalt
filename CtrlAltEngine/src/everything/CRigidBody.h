/*
@group	CTRL ALT
@file	CRigidBody.h
@brief	Rigidbody Component
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/

#ifndef CRIGIDBODY_H
#define CRIGIDBODY_H
#include "../src/pch.h" 
#include <../libs/glm/glm.hpp> // implement our own
#include "../Math/MathLib.h"

namespace Component {


	struct CRigidBody
	{
		MathLib::vec2 vel;

		CRigidBody(MathLib::vec2 vel = MathLib::vec2(0, 0))
		{
			this->vel = vel;
		}
	};
}

#endif