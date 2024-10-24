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
	/******************************************************************************/
	/*
		A 2D Vector class with float of x and y.
	 */
	 /******************************************************************************/
	class vec2
	{
	public:

		union
		{
			struct
			{
				float x, y;
			};
			float elements[2];
		};
		/******************************************************************************/
		/*
			A default contructor that initialises the vector as 0,0.
		 */
		 /******************************************************************************/
		vec2() :x{ 0.f }, y{ 0.f }
		{
		}

		/******************************************************************************/
		/*
			A contructor that takes in 2 floats and initialises the vector with the input.
		 */
		 /******************************************************************************/
		vec2(float inx, float iny) : x{ inx }, y{ iny }
		{
		}

		/******************************************************************************/
		/*
			A contructor that takes in 2 int and converts it to float and initialises the vector with the input.
		 */
		 /******************************************************************************/
		vec2(int inx, int iny) : x{ (float)inx }, y{ (float)iny }
		{
		}

		/******************************************************************************/
		/*
			A contructor that takes in 2 doubles and converts it to float and initialises the vector with the input.
		 */
		 /******************************************************************************/
		vec2(double inx, double iny) : x{ (float)inx }, y{ (float)iny }
		{
		}

		/******************************************************************************/
		/*
			A copy constructor that constructs a vec2 object with another vec2 object.
		 */
		 /******************************************************************************/
		vec2(const vec2&);

		/******************************************************************************/
		/*
			A copy assignment operator that assigns a vec2 object with another vec2 object.
		 */
		 /******************************************************************************/
		vec2 operator=(const vec2&);

		/******************************************************************************/
		/*
			Swap functions that swaps 2 vec2.
		 */
		 /******************************************************************************/
		void swap(vec2&, vec2&);
		void swap(vec2&);

		/******************************************************************************/
		/*
			Scaling operators that scale a vector by a float or int input.
		 */
		 /******************************************************************************/
		vec2& operator*=(float);
		vec2& operator*=(const vec2&);

		/******************************************************************************/
		/*
			Scaling operators that scale a vector by a float or int input.
		 */
		 /******************************************************************************/
		vec2& operator/=(float);
		vec2& operator/=(const vec2&);

		/******************************************************************************/
		/*
			Addition operators that adds 2 vectors together.
		 */
		 /******************************************************************************/
		vec2& operator+=(const vec2&);

		/******************************************************************************/
		/*
			Subtraction operators that subtracts a vector from another vector.
		 */
		 /******************************************************************************/
		vec2& operator-=(const vec2&);

		/******************************************************************************/
		/*
			Normalise a vector.
		 */
		 /******************************************************************************/
		void normalise();
		float vec2Length();
		float vec2SquareLength();

		/******************************************************************************/
		/*
			Gets the distance between 2 vectors.
		 */
		 /******************************************************************************/
		float vec2Dist(vec2&, vec2&);
		float vec2DistSquare(vec2&, vec2&);

		/******************************************************************************/
		/*
			Dot product operator and function of 2 vectors
		 */
		 /******************************************************************************/
		float operator*(vec2&);
		float vec2Dot(vec2&);

		/******************************************************************************/
		/*
			Cross product operator and function of 2 vectors
		 */
		 /******************************************************************************/
		float operator^(vec2&);
		float vec2Cross(vec2&);

		/******************************************************************************/
		/*
			Accessors to get the x and y value of a vector.
		 */
		 /******************************************************************************/
		const float& operator[](int) const;

		/******************************************************************************/
		/*
			Modifiers to set the x and y value of a vector.
		 */
		 /******************************************************************************/
		float& operator[](int);

		/******************************************************************************/
		/*
			Bool equality for all same x,y
		*/
		/******************************************************************************/
		bool operator==(const vec2&);
		bool operator!=(const vec2&);

		/******************************************************************************/
		/*
			Negate operator for vec2
		*/
		/******************************************************************************/
		vec2 operator-() const;

	};


	/******************************************************************************/
	/*
		Scaling operators that scale a vector by a float or int input.
	 */
	 /******************************************************************************/
	vec2 operator*(const vec2&, float);
	vec2 operator*(const vec2&, const vec2&);

	/******************************************************************************/
	/*
		Scaling operators that scale a vector by a float or int input.
	*/
	/******************************************************************************/
	vec2 operator/(const vec2&, float);
	vec2 operator/(const vec2&, const vec2&);

	/******************************************************************************/
	/*
		Addition operators that adds 2 vectors together.
	*/
	/******************************************************************************/
	vec2 operator+(const vec2&, const vec2&);

	/******************************************************************************/
	/*
		Subtraction operators that subtracts a vector from another vector.
	*/
	/******************************************************************************/
	vec2 operator-(const vec2&, const vec2&);


	/******************************************************************************/
	/*
		A 3D Vector class with float of x and y.
	 */
	 /******************************************************************************/
	class vec3
	{
	public:
		float x, y, z;

		/******************************************************************************/
		/*
			A default contructor that initialises the vector as 0,0.
		*/
		/******************************************************************************/
		vec3() :x{ 0.f }, y{ 0.f }, z{ 0.f }
		{
		}

		/******************************************************************************/
		/*
			A contructor that initialises the vector with float inputs.
		*/
		/******************************************************************************/
		vec3(float inx, float iny, float inz) : x{ inx }, y{ iny }, z{ inz }
		{
		}

		/******************************************************************************/
		/*
			A contructor that initialises the vector with int inputs.
		*/
		/******************************************************************************/
		vec3(int inx, int iny, int inz) : x{ (float)inx }, y{ (float)iny }, z{ (float)inz }
		{
		}

		/******************************************************************************/
		/*
			A contructor that initialises the vector with double inputs.
		*/
		/******************************************************************************/
		vec3(double inx, double iny, double inz) : x{ (float)inx }, y{ (float)iny }, z{ (float)inz }
		{
		}

		/******************************************************************************/
		/*
			A copy contructor that initialises the vec3 with another vec3.
		*/
		/******************************************************************************/
		vec3(const vec3&);

		/******************************************************************************/
		/*
			A copy assignment operator that assigns a vec3 object with another vec3 object.
		*/
		/******************************************************************************/
		vec3 operator=(const vec3&);

		/******************************************************************************/
		/*
			Swap functions that swaps 2 vec3.
		*/
		/******************************************************************************/
		void swap(vec3&, vec3&);

		/******************************************************************************/
		/*
			Scaling operators that scale a vector by a float or int input.
		*/
		/******************************************************************************/
		vec3& operator*=(float);
		vec3& operator*=(const vec3&);

		/******************************************************************************/
		/*
			Scaling operators that scale a vector by a float or int input.
		*/
		/******************************************************************************/
		vec3& operator/=(float);
		vec3& operator/=(const vec3&);

		/******************************************************************************/
		/*
			Addition operators that adds 2 vectors together.
		*/
		/******************************************************************************/
		vec3& operator+=(const vec3&);

		/******************************************************************************/
		/*
			Subtraction operators that subtract 1 vector from another vector.
		*/
		/******************************************************************************/
		vec3& operator-=(const vec3&);

		/******************************************************************************/
		/*
			Normalise a vector.
		*/
		/******************************************************************************/
		void normalise(vec3&);

		/******************************************************************************/
		/*
			Accessors to get the x and y and z value of a vector.
		*/
		/******************************************************************************/
		const float& operator[](int) const;

		/******************************************************************************/
		/*
			Modifiers to set the x and y and z value of a vector.
		*/
		/******************************************************************************/
		float& operator[](int);

		/******************************************************************************/
		/*
			Bool equality for all same x,y,z
		*/
		/******************************************************************************/
		bool operator==(const vec3&);
		bool operator!=(const vec3&);

		/******************************************************************************/
		/*
			Negate operator for vec2
		*/
		/******************************************************************************/
		vec3 operator-() const;

	};

	/******************************************************************************/
	/*
		Scaling operators that scale a vector by a float or int input.
	*/
	/******************************************************************************/
	vec3 operator*(const vec3&, float);
	vec3 operator*(const vec3&, const vec3&);


	/******************************************************************************/
	/*
		Scaling operators that scale a vector by a float or int input.
	*/
	/******************************************************************************/
	vec3 operator/(const vec3&, float);
	vec3 operator/(const vec3&, const vec3&);

	/******************************************************************************/
	/*
		Addition operators that adds 2 vectors together.
	*/
	/******************************************************************************/
	vec3 operator+(const vec3&, const vec3&);

	/******************************************************************************/
	/*
		Subtraction operators that subtract 1 vector from another vector.
	*/
	/******************************************************************************/
	vec3 operator-(const vec3&, const vec3&);

	/******************************************************************************/
	/*
		Convert a 2D vector to a 3D vector.
	*/
	/******************************************************************************/
	vec3 to3D(const vec2&, float z = 0.f);

	/******************************************************************************/
	/*
		Convert a 3D vector to a 2D vector by ridding of the z value.
	*/
	/******************************************************************************/
	vec2 to2D(const vec3&);


	/******************************************************************************/
	/*
		A function to print out a 2D vector.
	 */
	 /******************************************************************************/
	std::ostream& operator<<(std::ostream&, const vec2&);

	/******************************************************************************/
	/*
		A function to print out a 3D vector.
	 */
	 /******************************************************************************/
	std::ostream& operator<<(std::ostream&, const vec3&);
}

#endif

