/*
@group	CTRL ALT
@file	Collision.h
@brief	Collision Functions to check if objects collide.
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/
#ifndef COLLISION_H
#define COLLISION_H

#include <iostream>

namespace Collision
{
	/******************************************************************************/
	/*
		A class to represent a Line segment from 2 points.
	 */
	 /******************************************************************************/
	class Line
	{
		private:
			MathLib::vec2 p0;
			MathLib::vec2 p1;
			MathLib::vec2 normal;
		public:
			Line() :p0{},p1{},normal{}{}
			Line(MathLib::vec2, MathLib::vec2);

			Line(Line&);
			Line& operator=(Line&);

			void swap(Line&, Line&);
	};

	/******************************************************************************/
	/*
		A class to represent a Circle with a centre and a radius.
	 */
	 /******************************************************************************/
	class Circle
	{
		private:
			MathLib::vec2 centre;
			float radius;
		public:
			Circle():centre{},radius{0.f}{}
			Circle(MathLib::vec2, float rad = 0.f);

			Circle(Circle&);
			Circle& operator=(Circle&);

			void swap(Circle&, Circle&);
	};

	struct AABB
	{
		MathLib::vec2 min;
		MathLib::vec2 max;
	};

	bool GridCollision(MathLib::vec2&, MathLib::vec2&);
	bool GridCollision(MathLib::vec3&, MathLib::vec3&);


	/******************************************************************************/
	/*
		A function that takes in the position of 2 objects and its width and height.
		It returns true if they intersect and false if they dont.
	 */
	 /******************************************************************************/
	bool CollisionIntersection_RectRect(const MathLib::vec2& pos1,	//Input position 1
										const float w1,				//Input width
										const float h1,				//Input height
										const MathLib::vec2& vel1,  //Input velocity
										const MathLib::vec2& pos2,	//Input position 2
										const float w2,				//Input width
										const float h2,				//Input height
										const MathLib::vec2& vel2,	//Input velocity
										float& firstTimeOfCollision); //Output: the calculated value of tFirst, below, must be returned here

	int CheckMovingCircleToLineEdge(bool withinBothLines,
		const Circle& circle,
		const MathLib::vec2& ptEnd,
		const Line& lineSeg,
		MathLib::vec2& interPt,
		MathLib::vec2& normalAtCollision,
		float& interTime);

	int CollisionIntersection_CircleLineSegment(const Circle& circle,
		const MathLib::vec2& ptEnd,
		const Line& lineSeg,
		MathLib::vec2& interPt,
		MathLib::vec2& normalAtCollision,
		float& interTime,
		bool& checkLineEdges);

}


#endif
