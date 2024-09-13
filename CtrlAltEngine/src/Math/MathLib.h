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

			//vector addition
			vec2 operator+(const vec2&);
			vec2& operator+=(const vec2&);

			//vector subtraction
			vec2 operator-(const vec2&);
			vec2& operator-=(const vec2&);

			//vector normalising
			void normalise(vec2&);

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

	//ostream vector2
	std::ostream& operator<<(std::ostream&, const vec2&);
	//ostream vector3
	std::ostream& operator<<(std::ostream&, const vec3&);
}

#endif
