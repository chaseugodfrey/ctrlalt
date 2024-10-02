#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <../libs/glm/glm.hpp> // implement our own
#include "../Math/MathLib.h"

using namespace MathLib;

namespace Component {

	
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