#ifndef FIXED_SCENE_H
#define FIXED_SCENE_H

#include "../ECS/ECS.h"
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>
#include "../Components/CRigidBody.h"
#include "../Components/CTransform.h"
namespace Scene {

class Scene {
private:
    ECS::Registry* registry;
    std::vector<ECS::Entity> sceneEntities;
	std::vector<std::pair<std::string, std::map<std::string, std::string>>> entityData;
    std::string sceneName;
    bool isLoaded;
    bool isDataLoaded;

    using ComponentDeserializer = std::function<void(ECS::Entity&, std::istream&)>;
    std::map<std::string, ComponentDeserializer> componentDeserializers;

public:
    Scene(ECS::Registry* reg) : registry(reg), isLoaded(false) {
        RegisterComponentDeserializers();
    }

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

        Logger::LogInfo("Component deserializers registered");
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

                auto deserializerIt = componentDeserializers.find(componentType);
                if (deserializerIt != componentDeserializers.end()) {
                    std::istringstream dataStream(componentData);
                    deserializerIt->second(entity, dataStream);
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
            // Need to implement a way to get component names from the registry
            // This is just a placeholder
            std::string componentList = GetComponentList(entity);
            Logger::LogInfo("Entity " + std::to_string(entity.GetID())+ " components:" + componentList);
        }
    }

    std::string GetComponentList(const ECS::Entity& entity) const {
        std::string componentList = "[";
        bool first = true;

        // Check for each component type
        if (entity.HasComponent<Component::CTransform>()) {
            componentList += "CTransform";
            first = false;
        }
        if (entity.HasComponent<Component::CRigidBody>()) {
            if (!first) componentList += ", ";
            componentList += "CRigidBody";
            first = false;
        }
        // Add more component checks here as needed

        componentList += "]";
        return componentList;
    }

    bool IsLoaded() const { return isLoaded; }
    bool IsDataLoaded() const { return isDataLoaded; }

};

}

#endif // FIXED_SCENE_H