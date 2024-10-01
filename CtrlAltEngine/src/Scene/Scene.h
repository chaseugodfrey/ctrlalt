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
    std::string sceneName;
    bool isLoaded;

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

    void LoadFromFile(const std::string& filePath) {
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
            int entityId;
            file >> line >> entityId; // Read "ID:" and the entity ID
            std::getline(file, line); // Consume the newline

            ECS::Entity entity = registry->CreateEntity();
            sceneEntities.push_back(entity);

            while (std::getline(file, line) && !line.empty()) {
                std::istringstream iss(line);
                std::string componentType;
                iss >> componentType;

                auto it = componentDeserializers.find(componentType);
                if (it != componentDeserializers.end()) {
                    it->second(entity, iss);
                }
                else {
                    Logger::LogInfo("Unknown component type: " + componentType);
                }
            }
        }

        file.close();
        Logger::LogInfo("Loaded " + std::to_string(sceneEntities.size()) + " entities from " + filePath);
    }



    void Load() {
        if (!isLoaded) {
            for (auto& entity : sceneEntities) {
                registry->AddEntityToSystems(entity);
            }
            isLoaded = true;
        }
    }

    void Unload() {
        if (isLoaded) {
            for (auto& entity : sceneEntities) {
                registry->RemoveEntityFromSystems(entity);
            }
            isLoaded = false;
        }
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

};

}

#endif // FIXED_SCENE_H