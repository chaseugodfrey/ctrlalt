/*!
\group		CtrlAlt
\file       SceneManager.h
\author     Jerron Teng
\par        t.junrongjerroni@digipen.edu
\date       Sep 17, 2024
\brief

This file declares the `SceneManager` class, which is responsible for managing multiple scenes in an ECS system.
It allows for adding, switching, and updating scenes, as well as serializing scene data.
*/
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

// INCLUDES
// =========================================================================================================
#include <unordered_map>
#include <memory>
#include <string>
#include "Scene.h"
#include "../ECS/ECS.h"
#include "../Components/CRigidBody.h"
#include "../Components/CTransform.h"
#include "../Components/CIdentifier.h"

namespace Scene
{
	class SceneManager
	{
	private:
		std::map<std::string, std::unique_ptr<Scene>> scenes;
		Scene* currentScene;
		ECS::Registry* registry;

	public:
		/*!
		@brief Constructor for SceneManager class
		Special scenarios: -
		@param -
		@return -
		\*________________________________________________________________*/
		SceneManager(ECS::Registry*);

		/*!
		@brief Function call for Editor to make changes in Scene
		Special scenarios: -
		@param std::string& entityType
		@return -
		\*________________________________________________________________*/
		void CreateEntityInScene(const std::string&);

		/*!
		@brief Function call to add a scene to the Editor given a filename and the filepath
		Special scenarios: -
		@param const std::string& name, const std::string& filePath
		@return -
		\*________________________________________________________________*/
		void AddScene(const std::string&, const std::string&);

		/*!
		@brief Function to serialize data to a file, called by Editor
		Special scenarios: -
		@param -
		@return -
		\*________________________________________________________________*/
		void SaveScene();

		/*!
		@brief To remove a scene when given scene
		Special scenarios: -
		@param -
		@return -
		\*________________________________________________________________*/
		void RemoveScene(const std::string&);

		/*!
		@brief Editor to call this function to Switch scenes in given registry
		Special scenarios: -
		@param const std::string& sceneName
		@return -
		\*________________________________________________________________*/
		void SwitchScene(const std::string&);

		/*!
		@brief Editor to call UpdateScene
		Special scenarios: -
		@param -
		@return -
		\*________________________________________________________________*/
		void UpdateScene();

		/*!
		@brief Get current Scene name in the form of an std::string
		Special scenarios: -
		@param -
		@return std::string 
		\*________________________________________________________________*/
		std::string GetSceneNumber();

		/*!
		@brief Returns current Scene
		Special scenarios: -
		@param -
		@return -
		\*________________________________________________________________*/
		Scene* GetScene();

	};
}

#endif