#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <../libs/glm/glm.hpp> // implement our own
#include "../Math/MathLib.h"

namespace Component {

	
	struct CTransform
	{
		MathLib::vec2 position;
		MathLib::vec2 scale;
		double rotation;

		CTransform(MathLib::vec2 position = MathLib::vec2(0, 0), MathLib::vec2 scale = MathLib::vec2(1, 1), double rotation = 0.0)
		{
			this->position = position;
			this->scale = scale;
			this->rotation = rotation;
		}
	};
}

#endif