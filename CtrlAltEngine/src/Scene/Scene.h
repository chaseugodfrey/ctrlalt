#ifndef SCENE_H
#define SCENE_H

#include "../ECS/ECS.h"
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>
#include "../Components/CRigidBody.h"
#include "../Components/CTransform.h"
#include "../Components/CIdentifier.h"
#include "../EntityFactory/EntityFactory.h"

namespace Scene {

class Scene {
private:
    ECS::Registry* registry;
	EntityFactory::EntityFactory entityFactory;
    std::vector<ECS::Entity> sceneEntities;
	std::vector<std::pair<std::string, std::map<std::string, std::string>>> entityData;
    std::string sceneName;
    bool isLoaded;
    bool isDataLoaded;
    std::size_t nextEntityID = 0;
    using ComponentDeserializer = std::function<void(ECS::Entity&, std::istream&)>;
    std::map<std::string, ComponentDeserializer> componentDeserializers;

public:
    Scene(ECS::Registry* reg)
        : registry(reg), isLoaded(false), isDataLoaded(false), entityFactory(reg) {
        RegisterComponentDeserializers();
    }

	std::size_t GetNextEntityID() {
        return nextEntityID++;
	}

	void SetSceneName(const std::string& name) { sceneName = name; }

    void RegisterComponentDeserializers() {
        RegisterComponentDeserializer<Component::CTransform>("CTransform",
            [](ECS::Entity& entity, std::istream& is) {
                float posX, posY, scaleX, scaleY, rotation;
                is >> posX >> posY >> scaleX >> scaleY >> rotation;
                entity.AddComponent<Component::CTransform>(
                    glm::vec2(posX, posY),
                    glm::vec2(scaleX, scaleY),
                    rotation
                );
                Logger::LogInfo("CTransform component added");
            });

        RegisterComponentDeserializer<Component::CRigidBody>("CRigidBody",
            [](ECS::Entity& entity, std::istream& is) {
                float velX, velY;
                is >> velX >> velY;
                entity.AddComponent<Component::CRigidBody>(glm::vec2(velX, velY));
                Logger::LogInfo("CRigidBody component added");
            });

        RegisterComponentDeserializer<Component::CIdentifier>("CIdentifier",
            [](ECS::Entity& entity, std::istream& is) {
                std::string name;
                is >> name;
                entity.AddComponent<Component::CIdentifier>(name);
                Logger::LogInfo("CIdentifier component added");
            });

        Logger::LogInfo("Component deserializers registered");
    }

    void CreateEntity(const std::string& entityType)
    {
        std::map<std::string, std::string> componentData;

		std::size_t entityID = GetNextEntityID();

        if (entityType == "Basic")
        {
            ECS::Entity entity = entityFactory.CreateBasicEntity();
            componentData["CTransform"] = SerializeTransform(entity.GetComponent<Component::CTransform>());
            sceneEntities.push_back(entity);
            entityData.push_back({ std::to_string(entityID), componentData });
            registry->AddEntityToSystems(entity);
        }
        else if (entityType == "Player")
        {
            ECS::Entity entity = entityFactory.CreatePlayerEntity();
            componentData["CTransform"] = SerializeTransform(entity.GetComponent<Component::CTransform>());
            componentData["CRigidBody"] = SerializeRigidBody(entity.GetComponent<Component::CRigidBody>());
            componentData["CIdentifier"] = SerializeIdentifier(entity.GetComponent<Component::CIdentifier>());
            sceneEntities.push_back(entity);
            entityData.push_back({ std::to_string(entityID), componentData });
            registry->AddEntityToSystems(entity);
        }
        else if (entityType == "Enemy")
        {
            ECS::Entity entity = entityFactory.CreateEnemyEntity();
            componentData["CTransform"] = SerializeTransform(entity.GetComponent<Component::CTransform>());
            componentData["CRigidBody"] = SerializeRigidBody(entity.GetComponent<Component::CRigidBody>());
            componentData["CIdentifier"] = SerializeIdentifier(entity.GetComponent<Component::CIdentifier>());
            sceneEntities.push_back(entity);
            entityData.push_back({ std::to_string(entityID), componentData });
            registry->AddEntityToSystems(entity);
        }
        else
        {
            Logger::LogInfo("Unknown entity type: " + entityType);
            return;
        }
    }

    std::string SerializeTransform(const Component::CTransform& transform)
    {
        std::stringstream ss;
        ss << transform.position.x << " " << transform.position.y << " "
            << transform.scale.x << " " << transform.scale.y << " "
            << transform.rotation;
        return ss.str();
    }

    std::string SerializeRigidBody(const Component::CRigidBody& rigidBody)
    {
        std::stringstream ss;
        ss << rigidBody.vel.x << " " << rigidBody.vel.y;
        return ss.str();
    }

    std::string SerializeIdentifier(const Component::CIdentifier& identifier)
    {
        return identifier.name;
    }

    template<typename T>
    void RegisterComponentDeserializer(const std::string& typeName, ComponentDeserializer deserializer) {
        componentDeserializers[typeName] = std::move(deserializer);
    }

    void LoadDataFromFile(const std::string& filePath) {
        if (isDataLoaded) return;

        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            return;
        }

        sceneEntities.clear();
        std::string line;
        int entityCount;
        file >> entityCount; // Read the number of entities
        std::getline(file, line); // Consume the newline

        for (int i = 0; i < entityCount; ++i) {
            std::map<std::string, std::string> components;
            std::string entityId;
            file >> line >> entityId; // Read "ID:" and the entity ID
            std::getline(file, line); // Consume the newline


            while (std::getline(file, line) && !line.empty()) {
                std::istringstream iss(line);
                std::string componentType, componentData;
                iss >> componentType;
                std::getline(iss, componentData);
                components[componentType] = componentData;
            }
            entityData.push_back({ entityId, components });
        }

        file.close();
        isDataLoaded = true;
        Logger::LogInfo("Loaded " + std::to_string(sceneEntities.size()) + " entities from " + filePath);
    }

    void SaveDataToFile()
    {
		sceneName[0] = std::tolower(sceneName[0]);
        std::string filePath = "Assets/" + sceneName + ".txt";

        std::ofstream file(filePath);
		if (!file.is_open()) {
			std::cerr << "Failed to open file: " << filePath << std::endl;
			return;
		}

        file << entityData.size() << std::endl;
        for (size_t i = 0; i < entityData.size(); ++i)
        {
			std::string entityId = entityData[i].first;
            std::map<std::string, std::string> components = entityData[i].second;
            file << "ID: " << entityId << std::endl;
			for (const auto& componentPair : components)
			{
				file << componentPair.first << " " << componentPair.second << std::endl;
			}
			file << std::endl;
        }
        file.close();
		Logger::LogInfo("Saved " + std::to_string(sceneEntities.size()) + " entities to " + filePath);
    }

    void Load() {
        if (isLoaded) {
            Logger::LogInfo("Scene already loaded: " + sceneName);
            return;
        }

        if (!isDataLoaded) {
            Logger::LogInfo("Data not preloaded for scene: " + sceneName);
            return;
        }

        for (size_t i = 0; i < entityData.size(); ++i) {
            const std::string& entityId = entityData[i].first;
            const std::map<std::string, std::string>& components = entityData[i].second;

            ECS::Entity entity = registry->CreateEntity();
            sceneEntities.push_back(entity);

            Logger::LogInfo("Creating entity " + entityId + " for scene: " + sceneName);

            for (const auto& componentPair : components) {
                const std::string& componentType = componentPair.first;
                const std::string& componentData = componentPair.second;

                auto it = componentDeserializers.find(componentType);
                if (it != componentDeserializers.end()) {
                    std::istringstream dataStream(componentData);
                    it->second(entity, dataStream);
                    Logger::LogInfo("Added component " + componentType + " to entity " + entityId);
                }
                else {
                    Logger::LogInfo("No deserializer found for component type: " + componentType);
                }
            }

            registry->AddEntityToSystems(entity);
        }

        isLoaded = true;
        Logger::LogInfo("Created " + std::to_string(sceneEntities.size()) + " entities for scene: " + sceneName);
    }

    void Unload() {
        if (!isLoaded) return;

        for (auto& entity : sceneEntities) {
            registry->KillEntity(entity);
            registry->Update();
        }
        sceneEntities.clear();
        //entityData.clear();
        nextEntityID = 0;
        isLoaded = false;
        Logger::LogInfo("Unloaded scene: " + sceneName);
    }

    void Update() {
        if (isLoaded) {
            // TODO: Implement scene-specific update logic
        }
    }

    // Debug function to print the number of entities and their components
    void DebugPrintEntityCount() const {
        std::cout << "Total entities in scene: " << sceneEntities.size() << std::endl;
        for (const auto& entity : sceneEntities) {
            Logger::LogInfo("Entity " + std::to_string(entity.GetID()));
            std::string componentList = GetComponentList(entity);
            Logger::LogInfo("Entity " + std::to_string(entity.GetID())+ " components:" + componentList);
        }
    }

    std::string GetComponentList(const ECS::Entity& entity) const {
        std::string componentList = "[";
        bool first = true;

        if (entity.HasComponent<Component::CTransform>()) {
            componentList += "CTransform";
			componentList += ", ";
			componentList += std::to_string(entity.GetComponent<Component::CTransform>().position.x);
			componentList += ", ";
			componentList += std::to_string(entity.GetComponent<Component::CTransform>().position.y);
    
            first = false;
        }
        if (entity.HasComponent<Component::CRigidBody>()) {
            if (!first) componentList += ", ";
            componentList += "CRigidBody";
			componentList += ", ";
			componentList += std::to_string(entity.GetComponent<Component::CRigidBody>().vel.x);
			componentList += ", ";
			componentList += std::to_string(entity.GetComponent<Component::CRigidBody>().vel.y);
            first = false;
        }
        if (entity.HasComponent<Component::CIdentifier>()) {
            if (!first) componentList += ", ";
            componentList += "CIdentifier";
			componentList += ", ";
			componentList += entity.GetComponent<Component::CIdentifier>().name;
            first = false;
        }
        componentList += "]";
        return componentList;
    }

    const std::string& GetCurrentSceneName() const { return sceneName; }

    bool IsLoaded() const { return isLoaded; }
    bool IsDataLoaded() const { return isDataLoaded; }

};

}

#endif