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
	vec2 vec2::operator=(vec2& inv)
	{
		vec2  tmp{ inv };
		swap(*this,tmp);
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

	vec2 operator/(const vec2& lhs,float scalar)
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
		tmp /= scalar;
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
	vec2 operator+( const vec2& lhs, const vec2& rhs)
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
	vec2 operator-(const vec2& lhs,const vec2& rhs)
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
	void vec2::normalise(vec2& inv)
	{
		inv.x /= vec2Length(inv);
		inv.y /= vec2Length(inv);
	}
	float vec2::vec2Length(vec2& inv)
	{
		return sqrt(inv.x * inv.x + inv.y * inv.y);
		
	}
	float vec2::vec2SquareLength(vec2& inv)
	{
		return (inv.x * inv.x + inv.y * inv.y);
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

	const float& vec2::X() const
	{
		return this->x;
	}
	const float& vec2::Y() const
	{
		return this->y;
	}

	float& vec2::X()
	{
		return this->x;
	}
	float& vec2::Y()
	{
		return this->y;
	}

	const float& vec2::operator[](int pos) const
	{
		if(pos < 0 || pos > 2)
			throw std::out_of_range("Index out of range");

		if(pos == 0)
			return x;
		if (pos == 1)
			return y;
	}
	float& vec2::operator[](int pos)
	{
		if(pos < 0 || pos > 2)
			throw std::out_of_range("Index out of range");
		
		if (pos == 0)
			return x;
		if (pos == 1)
			return y;
	}

	


	//Vec3


	vec3::vec3(const vec3& inv)
	{
		x = inv.x;
		y = inv.y;
		z = inv.z;
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
		this->x *= inv.X();
		this->y *= inv.Y();
		this->z *= inv.Z();

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
		this->x /= inv.X();
		this->y /= inv.Y();
		this->z /= inv.Z();

		return *this;
	}

	//vector addition
	vec3 operator+(const vec3& lhs,const vec3& rhs)
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
		float mag = sqrt(inv.x * inv.x + inv.y * inv.y + inv.z*inv.z);

		inv.x /= mag;
		inv.y /= mag;
		inv.z /= mag;
	}

	//accessor
	float vec3::X() const
	{
		return this->x;
	}
	float vec3::Y() const
	{
		return this->y;
	}
	float vec3::Z() const
	{
		return this->z;
	}

	const float& vec3::operator[](int pos) const
	{
		if (pos < 0 || pos > 3)
			throw std::out_of_range("Index out of range");

		if (pos == 0)
			return x;
		else if (pos == 1)
			return y;
		else if (pos == 2)
			return z;
	}
	float& vec3::operator[](int pos)
	{
		if (pos < 0 || pos > 3)
			throw std::out_of_range("Index out of range");

		if (pos == 0)
			return x;
		else if (pos == 1)
			return y;
		else if (pos == 2)
			return z;
	}

	//modifier
	void vec3::X(float in)
	{
		this->x = in;
	}
	void vec3::Y(float in)
	{
		this->y = in;
	}
	void vec3::Z(float in)
	{
		this->z = in;
	}

	vec3 to3D(const vec2& inv, float z)
	{
		return vec3(inv.X(), inv.Y(), z);
	}

	vec2 to2D(const vec3& inv)
	{
		return vec2(inv.X(), inv.Y());
	}


	// M3x3


	m3x3::m3x3(const float* pArr)
	{
		for (size_t i = 0; i < 9; i++)
		{
			m[i] = *pArr++;
		}
		size_t counter = 0;
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				m2[i][j] = m[counter++];
			}
		}

		m00 = m[0];
		m01 = m[1];
		m02 = m[2];
		m10 = m[3];
		m11 = m[4];
		m12 = m[5];
		m20 = m[6];
		m21 = m[7];
		m22 = m[8];
	}
	m3x3::m3x3(float _00, float _01, float _02,
		float _10, float _11, float _12,
		float _20, float _21, float _22)
	{
		m2[0][0] = m[0] = m00 = _00;
		m2[0][1] = m[1] = m01 = _01;
		m2[0][2] = m[2] = m02 = _02;
		m2[1][0] = m[3] = m10 = _10;
		m2[1][1] = m[4] = m11 = _11;
		m2[1][2] = m[5] = m12 = _12;
		m2[2][0] = m[6] = m20 = _20;
		m2[2][1] = m[7] = m21 = _21;
		m2[2][2] = m[8] = m22 = _22;

	}
	m3x3::m3x3(const m3x3& rhs)
	{
		m2[0][0] = m[0] = m00 = rhs.m00;
		m2[0][1] = m[1] = m01 = rhs.m01;
		m2[0][2] = m[2] = m02 = rhs.m02;
		m2[1][0] = m[3] = m10 = rhs.m10;
		m2[1][1] = m[4] = m11 = rhs.m11;
		m2[1][2] = m[5] = m12 = rhs.m12;
		m2[2][0] = m[6] = m20 = rhs.m20;
		m2[2][1] = m[7] = m21 = rhs.m21;
		m2[2][2] = m[8] = m22 = rhs.m20	;

	}
	m3x3& m3x3::operator=(const m3x3& rhs)
	{
		m3x3  tmp{ rhs };
		swap(*this, tmp);
		 
		return *this;
	}
	void m3x3::swap(m3x3& lhs, m3x3& rhs)
	{
		std::swap(lhs.m00, rhs.m00);
		std::swap(lhs.m01, rhs.m01);
		std::swap(lhs.m02, rhs.m02);
		std::swap(lhs.m10, rhs.m10);
		std::swap(lhs.m11, rhs.m11);
		std::swap(lhs.m12, rhs.m12);
		std::swap(lhs.m20, rhs.m20);
		std::swap(lhs.m21, rhs.m21);
		std::swap(lhs.m22, rhs.m22);
	}

	float* m3x3::getM()
	{
		return m;
	}
	


	// OSTREAMS

	//ostream for vector2
	std::ostream& operator<<(std::ostream& os , const vec2& inv)
	{
		os << '(' << inv.X() << ',' << inv.Y() << ')';
		return os;
	}

	//ostream for vector3
	std::ostream& operator<<(std::ostream& os , const vec3& inv)
	{
		os << '(' << inv.X() << ',' << inv.Y() << ',' << inv.Z() << ')';
		return os;
	}
	//ostream for matrix3x3
	/*std::ostream& operator<<(std::ostream&, const m3x3&)
	{

	}*/
}