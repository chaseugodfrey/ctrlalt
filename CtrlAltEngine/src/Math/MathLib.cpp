#include "MathLib.h"
#include <algorithm>
#include <iostream>

namespace MathLib
{
	//Vec2

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

	float vec2::getX() const
	{
		return this->x;
	}
	float vec2::getY() const
	{
		return this->y;
	}

	void vec2::setX(float in)
	{
		this->x = in;
	}
	void vec2::setY(float in)
	{
		this->y = in;
	}


	//Vec3


	vec3::vec3(vec3& inv)
	{
		vec3(inv.x, inv.y,inv.z);
	}
	vec3 vec3::operator=(vec3& inv)
	{
		vec3  tmp{ inv };
		swap(*this, tmp);
		return *this;
	}

	void vec3::swap(vec3& lhs, vec3& rhs)
	{
		std::swap(lhs.x, rhs.x);
		std::swap(lhs.y, rhs.y);
		std::swap(lhs.z, rhs.z);
	}

	vec3 vec3::operator*(const float scalar)
	{
		vec3 tmp{ *this };
		tmp.x *= scalar;
		tmp.y *= scalar;
		tmp.z *= scalar;

		return tmp;
	}
	vec3& vec3::operator*=(const float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;

		return *this;
	}
	//vector addition
	vec3 vec3::operator+(const vec3& rhs)
	{
		vec3 tmp{ *this };
		tmp += rhs;
		return tmp;
	}

	vec3& vec3::operator+=(const vec3& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;

		return *this;
	}

	//vector subtraction
	vec3 vec3::operator-(const vec3& rhs)
	{
		vec3 tmp{ *this };
		tmp -= rhs;
		return tmp;
	}
	vec3& vec3::operator-=(const vec3& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;

		return *this;
	}

	//vector normalising
	void vec3::normalise(vec3& inv)
	{
		float mag = sqrt(inv.x * inv.x + inv.y * inv.y + inv.z*inv.z);

		inv.x /= mag;
		inv.y /= mag;
		inv.z /= mag;
	}

	//accessor
	float vec3::getX() const
	{
		return this->x;
	}
	float vec3::getY() const
	{
		return this->y;
	}
	float vec3::getZ() const
	{
		return this->z;
	}

	//modifier
	void vec3::setX(float in)
	{
		this->x = in;
	}
	void vec3::setY(float in)
	{
		this->y = in;
	}
	void vec3::setZ(float in)
	{
		this->z = in;
	}


	//ostream for vector2
	std::ostream& operator<<(std::ostream& os , const vec2& inv)
	{
		os << '(' << inv.getX() << ',' << inv.getY() << ')';
		return os;
	}

	//ostream for vector3
	std::ostream& operator<<(std::ostream& os, const vec3& inv)
	{
		os << '(' << inv.getX() << ',' << inv.getY() << ',' << inv.getZ() << ')';
		return os;
	}
}