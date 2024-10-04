/******************************************************************************/
/*!
\group  	CtrlAlt
\file		ECS.h
\author 	Michael Lazaroo
\par    	m.lazaroo@digipen.edu
\date   	Sep 08, 2024
\brief		ECS Implementation


Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <../libs/glm/glm.hpp> // implement our own
#include "../Math/MathLib.h"

using namespace MathLib;

namespace Component {

	/**
	 * @brief Transform component
	 * @data position The position of the entity
	 * @data scale The scale of the entity
	 * @data rotation The rotation of the entity
	 */
	struct CTransform
	{
		vec2 position;
		vec2 scale;
		double rotation;

		CTransform(vec2 position = vec2(0, 0), vec2 scale = vec2(1, 1), double rotation = 0.0)
		{
			this->position = position;
			this->scale = scale;
			this->rotation = rotation;
		}
	};
}

#endif