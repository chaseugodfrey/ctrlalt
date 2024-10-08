/*
@group	CTRL ALT
@file	MathLib.cpp
@brief	Mathematics library with vector 2D, vector 3D, matrix 3x3.
		Includes funcitons to manipukate and use such vectors and matrices.
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/

#include "MathLib.h"

#include <algorithm>
#include <iostream>

namespace MathLib
{
	//Vec2

	vec2::vec2(const vec2& inv)
	{
		x = inv.x;
		y = inv.y;
	}
	vec2 vec2::operator=(const vec2& inv)
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

	void vec2::swap(vec2& rhs)
	{
		std::swap(this->x, rhs.x);
		std::swap(this->y, rhs.y);
	}

	vec2 operator*(const vec2& lhs, float scalar)
	{
		vec2 tmp{ lhs };
		tmp *= scalar;

		return tmp;
	}
	vec2& vec2::operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;

		return *this;
	}

	vec2& vec2::operator*=(const vec2& inv)
	{
		x *= inv.x;
		y *= inv.y;

		return *this;
	}

	vec2 operator*(const vec2& lhs, const vec2& rhs)
	{
		vec2 tmp{ lhs };
		tmp *= rhs;

		return tmp;
	}

	vec2 operator/(const vec2& lhs, float scalar)
	{
		vec2 tmp{ lhs };
		tmp /= scalar;
		return tmp;
	}
	vec2& vec2::operator/=(float scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		return *this;
	}

	vec2 operator/(const vec2& lhs, int scalar)
	{
		vec2 tmp{ lhs };
		tmp /= (float)scalar;
		return tmp;
	}
	vec2& vec2::operator/=(const vec2& inv)
	{
		x /= inv.x;
		y /= inv.y;

		return *this;
	}

	vec2 operator/(const vec2& lhs, const vec2& rhs)
	{
		vec2 tmp{ lhs };
		tmp /= rhs;

		return tmp;
	}

	//vector addition
	vec2 operator+(const vec2& lhs, const vec2& rhs)
	{
		vec2 tmp{ lhs };
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
	vec2 operator-(const vec2& lhs, const vec2& rhs)
	{
		vec2 tmp{ lhs };
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
	void vec2::normalise()
	{
		x /= this->vec2Length();
		y /= this->vec2Length();
	}
	float vec2::vec2Length()
	{
		return sqrt(x * x + y * y);

	}
	float vec2::vec2SquareLength()
	{
		return (x * x + y * y);
	}

	float vec2::vec2Dist(vec2& p0, vec2& p1)
	{
		return sqrt((p0.x - p1.x) * (p0.x - p1.x) + (p0.y - p1.y) * (p0.y - p1.y));
	}
	float vec2::vec2DistSquare(vec2& p0, vec2& p1)
	{
		return (p0.x - p1.x) * (p0.x - p1.x) + (p0.y - p1.y) * (p0.y - p1.y);
	}

	float vec2::operator*(vec2& rhs)
	{
		return this->x * rhs.x + this->y * rhs.y;
	}
	float vec2::vec2Dot(vec2& rhs)
	{
		return this->x * rhs.x + this->y * rhs.y;
	}
	float vec2::operator^(vec2& rhs)
	{
		return this->x * rhs.y - this->y * rhs.x;
	}
	float vec2::vec2Cross(vec2& rhs)
	{
		return this->x * rhs.y - this->y * rhs.x;
	}

	const float& vec2::operator[](int pos) const
	{
		if (pos < 0 || pos >= 2)
			throw std::out_of_range("Index out of range");

		if (pos == 0)
			return x;

		return y;
	}
	float& vec2::operator[](int pos)
	{
		if (pos < 0 || pos >= 2)
			throw std::out_of_range("Index out of range");

		if (pos == 0)
			return x;

		return y;
	}

	bool vec2::operator==(const vec2& rhs)
	{
		return (x == rhs.x && y == rhs.y);
	}
	bool vec2::operator!=(const vec2& rhs)
	{
		return (x != rhs.x && y != rhs.y);
	}

	vec2 vec2::operator-() const {
		return vec2(-x, -y);
	}




	//Vec3


	vec3::vec3(const vec3& inv)
	{
		x = inv.x;
		y = inv.y;
		z = inv.z;
	}

	vec3 vec3::operator=(const vec3& inv)
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

	vec3 operator*(const vec3& lhs, float scalar)
	{
		vec3 tmp{ lhs };
		tmp *= scalar;

		return tmp;
	}

	vec3 operator*(const vec3& lhs, const vec3& rhs)
	{
		vec3 tmp{ lhs };
		tmp *= rhs;
		return tmp;
	}
	vec3& vec3::operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;

		return *this;
	}
	vec3& vec3::operator*=(const vec3& inv)
	{
		this->x *= inv.x;
		this->y *= inv.y;
		this->z *= inv.z;

		return *this;
	}

	//scale vector div
	vec3 operator/(const vec3& lhs, float scalar)
	{
		vec3 tmp{ lhs };
		tmp /= scalar;

		return tmp;
	}
	vec3 operator/(const vec3& lhs, const vec3& rhs)
	{
		vec3 tmp{ lhs };
		tmp /= rhs;

		return tmp;
	}
	vec3& vec3::operator/=(float scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		this->z /= scalar;

		return *this;
	}
	vec3& vec3::operator/=(const vec3& inv)
	{
		this->x /= inv.x;
		this->y /= inv.y;
		this->z /= inv.z;

		return *this;
	}

	//vector addition
	vec3 operator+(const vec3& lhs, const vec3& rhs)
	{
		vec3 tmp{ lhs };
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
	vec3 operator-(const vec3& lhs, const vec3& rhs)
	{
		vec3 tmp{ lhs };
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
		float mag = sqrt(inv.x * inv.x + inv.y * inv.y + inv.z * inv.z);

		inv.x /= mag;
		inv.y /= mag;
		inv.z /= mag;
	}

	//accessor

	const float& vec3::operator[](int pos) const
	{
		if (pos < 0 || pos >= 3)
			throw std::out_of_range("Index out of range");

		if (pos == 0)
			return x;
		else if (pos == 1)
			return y;

		return z;
	}

	//modifier
	float& vec3::operator[](int pos)
	{
		if (pos < 0 || pos >= 3)
			throw std::out_of_range("Index out of range");

		if (pos == 0)
			return x;
		else if (pos == 1)
			return y;

		return z;
	}

	

	bool vec3::operator==(const vec3& rhs)
	{
		if (x == rhs.x && y == rhs.y && z == rhs.z)
			return true;
		return false;
	}
	bool vec3::operator!=(const vec3& rhs)
	{
		if (x != rhs.x && y != rhs.y && z != rhs.z)
			return true;
		return false;
	}

	vec3 vec3::operator-() const {
		return vec3(-x, -y,-z);
	}

	vec3 to3D(const vec2& inv, float z)
	{
		return vec3(inv.x, inv.y, z);
	}

	vec2 to2D(const vec3& inv)
	{
		return vec2(inv.x, inv.y);
	}



	// OSTREAMS

	//ostream for vector2
	std::ostream& operator<<(std::ostream& os, const vec2& inv)
	{
		os << '(' << inv.x << ',' << inv.y << ')';
		return os;
	}

	//ostream for vector3
	std::ostream& operator<<(std::ostream& os, const vec3& inv)
	{
		os << '(' << inv.x << ',' << inv.y << ',' << inv.z << ')';
		return os;
	}
}