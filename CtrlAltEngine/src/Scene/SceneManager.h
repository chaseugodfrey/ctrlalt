#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <unordered_map>
#include <memory>
#include <string>
#include "Scene.h"
#include "../ECS/ECS.h"
#include "../Logger/Logger.h"
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
		SceneManager(ECS::Registry* registry) : registry(registry), currentScene(nullptr) {
		
		}

		void CreateEntityInScene(const std::string& entityType)
		{
			if (currentScene)
			{
				currentScene->CreateEntity(entityType);
				currentScene->DebugPrintEntityCount();
			}
		}

		void AddScene(const std::string& name, const std::string& filePath)
		{
			auto scene = std::make_unique<Scene>(registry);
			scene->LoadDataFromFile(filePath);
			scenes[name] = std::move(scene);
			Logger::LogInfo("Scene added: " + name);
		}

		void SaveScene(const std::string& scenePath)
		{
			currentScene->SaveDataToFile(scenePath);
		}

		void RemoveScene(const std::string& scene)
		{
			scenes.erase(scene);
		}

		void SwitchScene(const std::string& scene)
		{

			auto it = scenes.find(scene);
			
			if (it->second.get() == currentScene)
			{
				Logger::LogInfo("Scene already active: " + scene);
				return;
			}

			if (it != scenes.end())
			{
				if(currentScene)
				currentScene->Unload();
				currentScene = it->second.get();
				if(!currentScene->IsLoaded())
				currentScene->Load();
				Logger::LogInfo("Switched to scene: " + scene);
				currentScene->DebugPrintEntityCount();
			}
			else
			{
				Logger::LogInfo("Error, no scene:" + scene);
			}
		}

		void UpdateScene()
		{
			if (currentScene) currentScene->Update();
		}

		Scene* GetScene()
		{
			return currentScene;
		}

		void LoadScene(const std::string& scenePath) {
			currentScene->LoadDataFromFile(scenePath);
			currentScene->Load(); // This adds entities to systems
		}

	};
}

#endif