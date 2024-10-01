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
			auto scene = std::make_unique<Scene>(registry);
			scene->LoadDataFromFile(filePath);
			scenes[name] = std::move(scene);
			Logger::LogInfo("Scene added: " + name);
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
				if(!currentScene->IsLoaded())
				currentScene->Load();
				Logger::LogInfo("Switched to scene: " + scene);
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


		void RegisterComponentDeserializers(Scene* scene) {
			for (auto& scene : scenes) {
				scene.second->RegisterComponentDeserializer<Component::CTransform>("CTransform",
					[](ECS::Entity& entity, std::istream& is) {
						float posX, posY, scaleX, scaleY, rotation;
						is >> posX >> posY >> scaleX >> scaleY >> rotation;
						entity.AddComponent<Component::CTransform>(
							glm::vec2(posX, posY),
							glm::vec2(scaleX, scaleY),
							rotation
						);
					});

				scene.second->RegisterComponentDeserializer<Component::CRigidBody>("CRigidBody",
					[](ECS::Entity& entity, std::istream& is) {
						float velX, velY;
						is >> velX >> velY;
						entity.AddComponent<Component::CRigidBody>(glm::vec2(velX, velY));
					});
			}
		}


		void LoadScene(const std::string& scenePath) {
			currentScene->LoadDataFromFile(scenePath);
			currentScene->Load(); // This adds entities to systems
		}

	};
}

#endif