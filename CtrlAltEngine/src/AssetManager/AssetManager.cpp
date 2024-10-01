#include "AssetManager.h"

////ONLY INCLUDE STB_IMAGE HERE
//#define STB_IMAGE_IMPLEMENTATION
////#define STBI_MALLOC
////#define STBI_REALLOC
////#define STBI_FREE
//#include "STB_Image/stb_image.h"
//
//////Search Asset directory for asset files
//#include <filesystem>
//#include <iostream>
//#include "../Logger/Logger.h"

namespace Engine {
	//For now directly load images inside render
	AssetManager::AssetManager() {
		return;

		////Load Assets
		//static const char* asset_directory = "../Assets/";
		//static const char* png_extention = ".png";
		//Logger::LogInfo("Loading PNG Assets..\n");
		////Loop get all of png extension in asset directory
		//for (std::filesystem::directory_entry const& dir : 
		//	std::filesystem::recursive_directory_iterator(asset_directory)) {
		//	//Prints path of asset, filename of asset without ext, ext of asset
		//	std::cout << "Path: " << dir.path() << " Asset: " << dir.path().stem() << " Extention: " << dir.path().extension() << std::endl;
		//	//ImageAsset asset;
		//	int x{}, y{}, n{};
		//	unsigned char* data = stbi_load(static_cast<const char*>(dir.path().string().c_str()), &x, &y, &n, STBI_rgb_alpha);
		//	if (data == NULL) {
		//		Logger::LogInfo(std::string("ERROR: Unable to load: ") + dir.path().filename().string().c_str());	//shouldnt reach here
		//		continue;
		//	}
		//	image_map.insert({ dir.path().stem().string(), {data, x, y}});
		//}
		//Logger::LogInfo("PNG Assets loaded..\n");
	}

	AssetManager::~AssetManager() {
		return;
		////Release Assets
		//Logger::LogInfo("Releasing Image Data");
		//for (std::pair<std::string, ImageAsset> const& kvp : image_map) {
		//	stbi_image_free(kvp.second.image_data);
		//}
		//Logger::LogInfo(std::string("Released Image Data"));
	}
}