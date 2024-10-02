/*
@group	CTRL ALT
@file	CGrid.h
@brief	Collision Functions to check if objects collide.
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/
#ifndef CGRID_H
#define CGRID_H

#include "../Math/MathLib.h"

namespace Component
{
	enum ANCHOR
	{
		CENTRE,
		BOT_LEFT,
		TOP_LEFT,
		BOT_RIGHT,
		TOP_RIGHT
	};

	/******************************************************************************/
	/*
		A class to represent a Line segment from 2 points.
	 */
	 /******************************************************************************/
	struct Grid
	{
		MathLib::vec2 pos;
		ANCHOR align;
		float cell_width, cell_height;
		int num_row, num_col;



		Grid(MathLib::vec2 pos = MathLib::vec2(0, 0),
			ANCHOR align = CENTRE,
			float cell_width = 1.f,
			float cell_height = 1.f,
			int num_row = 1,
			int num_col = 1);
	};
}

#endif


