/*
@group	CTRL ALT
@file	CGrid.cpp
@brief	Collision Functions to check if objects collide.
Created by Muhammad Rayan
muhammadrayan.b@digipen.edu
*/

#include "CGrid.h"

namespace Component
{
	Grid::Grid(MathLib::vec2 pos,
		ANCHOR align,
		float cell_width,
		float cell_height,
		int num_row,
		int num_col)
	{
		this->pos = pos;
		this->cell_width = cell_width;
		this->cell_height = cell_height;
		this->num_row = num_row;
		this->num_col = num_col;
	}


}