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

	//ostream vector
	std::ostream& operator<<(std::ostream&, const vec2&);
}

#endif
