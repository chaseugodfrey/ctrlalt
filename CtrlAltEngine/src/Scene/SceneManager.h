#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <unordered_map>
#include <memory>
#include <string>
#include "Scene.h"
#include "../ECS/ECS.h"
#include "../Logger/Logger.h"

namespace Scene
{
	class SceneManager
	{
	private:
		std::map<std::string, std::unique_ptr<Scene>> scenes;
		Scene* currentScene;
		ECS::Registry* registry;

	public:
		SceneManager(ECS::Registry* registry) : registry(registry), currentScene(nullptr) {}

		void AddScene(const std::string& name, const std::string& filePath)
		{
			scenes[name] = std::make_unique<Scene>(registry);
			scenes[name]->LoadFromFile(filePath);
		}

		void RemoveScene(const std::string& scene)
		{
			scenes.erase(scene);
		}

		void SwitchScene(const std::string& scene)
		{
			auto it = scenes.find(scene);
			if (it != scenes.end())
			{
				if(currentScene)
				currentScene->Unload();
				currentScene = it->second.get();
				currentScene->Load();
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
	};
}

#endif