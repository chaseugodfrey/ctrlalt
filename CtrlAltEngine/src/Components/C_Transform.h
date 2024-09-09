#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <../libs/glm/glm.hpp> // implement our own

struct C_Transform
{
	glm::vec2 position;
	glm::vec2 scale;
	double rotation;

	C_Transform(glm::vec2 position = glm::vec2(0,0), glm::vec2 scale = glm::vec2(1,1), double rotation = 0.0)
	{
		this->position = position;
		this->scale = scale;
		this->rotation = rotation;
	}
};


#endif