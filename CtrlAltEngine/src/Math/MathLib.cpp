#include "MathLib.h"
#include <algorithm>
#include <iostream>

namespace MathLib
{
	vec2::vec2(vec2& inv)
	{
		vec2(inv.x, inv.y);
	}
	vec2 vec2::operator=(vec2& inv)
	{
		vec2  tmp{ inv };
		swap(*this, tmp);
		return *this;
	}

	void vec2::swap(vec2& lhs, vec2& rhs)
	{
		std::swap(lhs.x, rhs.x);
		std::swap(lhs.y, rhs.y);
	}

	vec2 vec2::operator*(const float scalar)
	{
		vec2 tmp{ *this };
		tmp.x *= scalar;
		tmp.y *= scalar;

		return tmp;
	}
	vec2& vec2::operator*=(const float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;

		return *this;
	}
	//vector addition
	vec2 vec2::operator+(const vec2& rhs)
	{
		vec2 tmp{ *this };
		tmp += rhs;
		return tmp;
	}

	vec2& vec2::operator+=(const vec2& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;

		return *this;
	}

	//vector subtraction
	vec2 vec2::operator-(const vec2& rhs)
	{
		vec2 tmp{ *this };
		tmp -= rhs;
		return tmp;
	}
	vec2& vec2::operator-=(const vec2& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;

		return *this;
	}

	//vector normalising
	void vec2::normalise(vec2& inv)
	{
		float mag = sqrt(inv.x * inv.x + inv.y * inv.y);

		inv.x /= mag;
		inv.y /= mag;
	}

	//accessor
	float vec2::getX() const
	{
		return this->x;
	}
	float vec2::getY() const
	{
		return this->y;
	}

	//modifier
	void vec2::setX(float in)
	{
		this->x = in;
	}
	void vec2::setY(float in)
	{
		this->y = in;
	}

	//ostream for vector
	std::ostream& operator<<(std::ostream& os , const vec2& inv)
	{
		os << '(' << inv.getX() << ',' << inv.getY() << ')';
		return os;
	}
}