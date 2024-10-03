#ifndef SCENE_H
#define SCENE_H

#include "../ECS/ECS.h"
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>
#include "../EntityFactory/EntityFactory.h"
#include "../Components/CRigidBody.h"
#include "../Components/CTransform.h"
#include "../Components/CIdentifier.h"
using namespace MathLib;

namespace Scene {

class Scene {
private:
    ECS::Registry* registry;
    std::string filePath;
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
    Scene(ECS::Registry* reg, const std::string& name, const std::string& path)
        : registry(reg), isLoaded(false), filePath(path), sceneName(name),isDataLoaded(false), entityFactory(reg) {
        RegisterComponentDeserializers();
    }

	std::size_t GetNextEntityID() {
        return nextEntityID++;
	}

	void SetSceneName(const std::string& name) { sceneName = name; }
    void RegisterComponentDeserializers();
    void CreateEntity(const std::string& entityType);

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

    void LoadEntityData();
    void Load();
    void SaveDataToFile();

    void Unload();
    void Update();

    // Debug function to print the number of entities and their components
    void DebugPrintEntityCount() const;
    std::string GetComponentList(const ECS::Entity& entity) const;
    const std::string& GetCurrentSceneName() const { return sceneName; }
    bool IsLoaded() const { return isLoaded; }
    bool IsDataLoaded() const { return isDataLoaded; }

    // FOR M1 PURPOSES

    void Scene3_PopulateScene();
    };

}

#endif