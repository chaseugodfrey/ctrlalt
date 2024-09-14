/*
@group	CTRL ALT
@file	MathLib.h
@brief	Mathematics library with vector 2D, vector 3D, matrix 3x3.
		Includes funcitons to manipukate and use such vectors and matrices.
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/

#ifndef MATHLIB_H
#define MATHLIB_H

#include <iostream>

namespace MathLib
{
	class vec2
	{
		private:
			float x, y;
			float m[2];

		public:
			//default constructor
			vec2() :x{ 0.f }, y{0.f}
			{
				m[0] = x;
				m[1] = y;
			}

			//constructor with float
			vec2(float inx, float iny) : x{ inx }, y{ iny }
			{
				m[0] = x;
				m[1] = y;
			}

			//constructor with int
			vec2(int inx, int iny) : x{ (float)inx}, y{ (float)iny}
			{
				m[0] = x;
				m[1] = y;
			}

			//constructor with double
			vec2(double inx, double iny) : x{ (float)inx }, y{ (float)iny }
			{
				m[0] = x;
				m[1] = y;
			}

			//copy constructor
			vec2(vec2&);

			//copy assignment 
			vec2 operator=(vec2&);

			//swap
			void swap(vec2&, vec2&);

			//scale vector
			vec2 operator*(float);
			vec2& operator*=(float);

			//scale vector div
			vec2 operator/(float);
			vec2& operator/=(float);

			//vector addition
			vec2 operator+(const vec2&);
			vec2& operator+=(const vec2&);

			//vector subtraction
			vec2 operator-(const vec2&);
			vec2& operator-=(const vec2&);

			//vector normalising
			void normalise(vec2&);
			float vec2Length(vec2&);
			float vec2SquareLength(vec2&);

			//distance
			float vec2Dist(vec2&, vec2&);
			float vec2DistSquare(vec2&, vec2&);

			//dot andd cross product
			float operator*(vec2&);
			float vec2Dot(vec2&);
			float operator^(vec2&);
			float vec2Cross(vec2&);

			//accessor
			float getX() const;
			float getY() const;

			//modifier
			void setX(float);
			void setY(float);

	};

	class vec3
	{
	private:
		float x, y,z;
		float m[3];

	public:
		//default constructor
		vec3() :x{ 0.f }, y{ 0.f },z{0.f}
		{
			m[0] = x;
			m[1] = y;
			m[2] = z;
		}

		//constructor with float
		vec3(float inx, float iny, float inz) : x{ inx }, y{ iny }, z{ inz }
		{
			m[0] = x;
			m[1] = y;
			m[2] = z;
		}

		//constructor with int
		vec3(int inx, int iny, int inz) : x{ (float)inx }, y{ (float)iny }, z{ (float)inz }
		{
			m[0] = x;
			m[1] = y;
			m[2] = z;
		}

		//constructor with double
		vec3(double inx, double iny, double inz) : x{ (float)inx }, y{ (float)iny }, z{ (float)inz }
		{
			m[0] = x;
			m[1] = y;
			m[2] = z;
		}

		//copy constructor
		vec3(vec3&);

		//copy assignment 
		vec3 operator=(vec3&);

		//swap
		void swap(vec3&, vec3&);

		//scale vector
		vec3 operator*(float);
		vec3& operator*=(float);

		//scale vector div
		vec3 operator/(float);
		vec3& operator/=(float);

		//vector addition
		vec3 operator+(const vec3&);
		vec3& operator+=(const vec3&);

		//vector subtraction
		vec3 operator-(const vec3&);
		vec3& operator-=(const vec3&);

		//vector normalising
		void normalise(vec3&);

		//accessor
		float getX() const;
		float getY() const;
		float getZ() const;

		//modifier
		void setX(float);
		void setY(float);
		void setZ(float);

	};

	class m3x3
	{
		float m00, m01, m02;
		float m10, m11, m12;
		float m20, m21, m22;

		float m[9];
		float m2[3][3];

		m3x3():m00(0.f), m01(0.f), m02(0.f), m10(0.f), m11(0.f), m12(0.f), m20(0.f), m21(0.f), m22(0.f) 
		{
			for (size_t i = 0; i < 9; i++)
			{
				m[i] = 0.f;
			}

			for (size_t i = 0; i < 3; i++)
			{
				for (size_t j = 0; j < 3; j++)
				{
					m2[i][j] = 0.f;
				}
			}
		}
		m3x3(const float* pArr);
		m3x3(float _00, float _01, float _02,
			float _10, float _11, float _12,
			float _20, float _21, float _22);
		m3x3& operator=(const m3x3& rhs);
		m3x3(const m3x3& rhs);
		void swap(m3x3&, m3x3&);
	};

	//ostream vector2
	std::ostream& operator<<(std::ostream&, const vec2&);
	//ostream vector3
	std::ostream& operator<<(std::ostream&, const vec3&);
	//ostream matrix3x3
	std::ostream& operator<<(std::ostream&, const m3x3&);
}

#endif
