#ifndef CRIGIDBODY_H
#define CRIGIDBODY_H

#include <../libs/glm/glm.hpp> // implement our own

namespace Component {


	struct CRigidBody
	{
		glm::vec2 vel;

		CRigidBody(glm::vec2 vel = glm::vec2(0, 0))
		{
			this->vel = vel;
		}
	};
}

#endif