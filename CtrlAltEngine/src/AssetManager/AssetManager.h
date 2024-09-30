#pragma once
/******************************************************************************/
/*!
\group  	CtrlAlt
\file		AssetManager.h
\author 	Elton Leosantosa
\par    	leosantosa.e@digipen.edu
\date   	Sep 26, 2024
\brief		AssetManager API


Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <unordered_map>
#include <string>
#include <vector>

namespace Engine {
	class ImageAsset;

	class AssetManager {
		std::unordered_map<std::string, ImageAsset> image_map;
	public:
		AssetManager();
		~AssetManager();
	};

	//Wrapper struct for an image asset
	class ImageAsset {
	public:
		ImageAsset(unsigned char* data, int x, int y, std::string name) : image_data(data), width(x), height(y), name(name) {};
		unsigned char*	image_data{};
		int				width{};
		int				height{};
		std::string		name{};
	};
}