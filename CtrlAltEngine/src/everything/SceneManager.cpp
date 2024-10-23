/*!
\group		CtrlAlt
\file       SceneManager.cpp
\author     Jerron Teng
\par        t.junrongjerroni@digipen.edu
\date       Sep 17, 2024
\brief

This file defines the `SceneManager` class, which is responsible for managing multiple scenes in an ECS system.
It allows for adding, switching, and updating scenes, as well as serializing scene data.
*/

// INCLUDES
// =========================================================================================================
#include "../src/pch.h"
#include "SceneManager.h"
#include <algorithm>
#include "../ECS/ECS.h"
#include "../Logger/Logger.h"
#include "../Components/CRigidBody.h"
#include "../Components/CTransform.h"
#include "../Components/CIdentifier.h"

namespace Scene
{
	/*!
	@brief Constructor for SceneManager class
	Special scenarios: -
	@param -
	@return -
	\*________________________________________________________________*/
	SceneManager::SceneManager(ECS::Registry* registry) : registry(registry), currentScene(nullptr) {

	}

	/*!
	@brief Function call for Editor to make changes in Scene
	Special scenarios: -
	@param std::string& entityType
	@return -
	\*________________________________________________________________*/
	void SceneManager::CreateEntityInScene()
	{
		if (currentScene)
		{
			currentScene->CreateEntity();
			currentScene->DebugPrintEntityCount();
		}
	}

	/*!
	@brief Function call to add a scene to the Editor given a filename and the filepath
	Special scenarios: -
	@param const std::string& name, const std::string& filePath
	@return -
	\*________________________________________________________________*/
	void SceneManager::AddScene(const std::string& name, const std::string& filePath)
	{
		auto scene = std::make_unique<Scene>(registry, name, filePath);
		scene->LoadEntityData();
		scenes[name] = std::move(scene);
		Logger::LogInfo("Scene added: " + name);
	}

	/*!
	@brief Function to serialize data to a file, called by Editor
	Special scenarios: -
	@param -
	@return -
	\*________________________________________________________________*/
	void SceneManager::SaveScene()
	{
		currentScene->SaveDataToFile();
	}

	/*!
	@brief To remove a scene when given scene
	Special scenarios: -
	@param -
	@return -
	\*________________________________________________________________*/
	void SceneManager::RemoveScene(const std::string& scene)
	{
		scenes.erase(scene);
	}

	/*!
	@brief Editor to call this function to Switch scenes in given registry
	Special scenarios: -
	@param const std::string& sceneName
	@return -
	\*________________________________________________________________*/
	void SceneManager::SwitchScene(const std::string& sceneName) {
		auto it = scenes.find(sceneName);
		if (it != scenes.end()) {
			if (currentScene)
				currentScene->Unload();
			currentScene = it->second.get();
			currentScene->Load();
			Logger::LogInfo("Switched to scene: " + sceneName);
			currentScene->DebugPrintEntityCount();
		}
		else {
			Logger::LogInfo("Error, no scene: " + sceneName);
		}
	}

	/*!
	@brief Editor to call UpdateScene
	Special scenarios: -
	@param -
	@return -
	\*________________________________________________________________*/
	void SceneManager::UpdateScene()
	{
		if (currentScene) currentScene->Update();
	}

	/*!
	@brief Get current Scene name in the form of an std::string
	Special scenarios: -
	@param -
	@return std::string
	\*________________________________________________________________*/
	std::string SceneManager::GetSceneNumber()
	{
		return currentScene->GetCurrentSceneName();
	}

	/*!
	@brief Returns current Scene
	Special scenarios: -
	@param -
	@return -
	\*________________________________________________________________*/
	Scene* SceneManager::GetScene()
	{
		return currentScene;
	}

}
