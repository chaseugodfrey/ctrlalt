/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Editor.cpp
\author 	Chase Rodrigues
\par    	rodrigues.i@digipen.edu
\date   	Sep 08, 2024
\brief

This file defines the `Scene` class which manages a collection of entities in an ECS system.
It provides functionality for loading and saving entity data, registering component deserializers,
and managing the scene's state.
*/
#ifndef SCENE_H
#define SCENE_H

// INCLUDES
// =========================================================================================================
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
    /*!
     * \brief Constructor for Scene class.
     *
     * Initializes a new scene with a given registry, name, and file path.
     * \param reg Pointer to the ECS registry.
     * \param name Name of the scene.
     * \param path File path to load or save the scene data.
     */
    Scene(ECS::Registry* reg, const std::string& name, const std::string& path)
        : registry(reg), isLoaded(false), filePath(path), sceneName(name),isDataLoaded(false), entityFactory(reg) {
        RegisterComponentDeserializers();
    }

    /*!
     * \brief Gets the next available entity ID and increments the internal counter.
     * \return The next unique entity ID.
     */
	std::size_t GetNextEntityID() {
        return nextEntityID++;
	}


    /*!
     * \brief Sets the name of the scene.
     * \param name The new name of the scene.
     */
	void SetSceneName(const std::string& name) { sceneName = name; }

    /*!
     * \brief Registers deserializers for various components in the scene.
     *
     * This function registers component deserializers such as for CTransform and CRigidBody,
     * allowing the scene to read component data from an input stream.
     */
    void RegisterComponentDeserializers();

    /*!
     * \brief Creates an entity of the specified type using the entity factory.
     * \param entityType The type of entity to create.
     */
    void CreateEntity(const std::string& entityType = "Basic");

    /*!
     * \brief Serializes the CTransform component of an entity into a string.
     * \param transform The CTransform component to serialize.
     * \return A string representing the serialized CTransform component.
     */
    std::string SerializeTransform(const Component::CTransform& transform)
    {
        std::stringstream ss;
        ss << transform.position.x << " " << transform.position.y << " "
            << transform.scale.x << " " << transform.scale.y << " "
            << transform.rotation;
        return ss.str();
    }

    /*!
    * \brief Serializes the CRigidBody component of an entity into a string.
    * \param rigidBody The CRigidBody component to serialize.
    * \return A string representing the serialized CRigidBody component.
    */
    std::string SerializeRigidBody(const Component::CRigidBody& rigidBody)
    {
        std::stringstream ss;
        ss << rigidBody.vel.x << " " << rigidBody.vel.y;
        return ss.str();
    }

    /*!
     * \brief Serializes the CIdentifier component of an entity into a string.
     * \param identifier The CIdentifier component to serialize.
     * \return A string representing the serialized CIdentifier component.
     */
    std::string SerializeIdentifier(const Component::CIdentifier& identifier)
    {
        return identifier.name;
    }

    /*!
     * \brief Registers a deserializer for a specific component type.
     * \tparam T The type of the component.
     * \param typeName The name of the component type.
     * \param deserializer A function to deserialize the component from an input stream.
     */
    template<typename T>
    void RegisterComponentDeserializer(const std::string& typeName, ComponentDeserializer deserializer) {
        componentDeserializers[typeName] = std::move(deserializer);
    }

    /*!
     * \brief Loads entity data from a file.
     *
     * Reads the entity and component data from the specified file and stores it for further processing.
     */
    void LoadEntityData();

    /*!
     * \brief Loads the scene from the file and creates entities and components based on the loaded data.
     */
    void Load();

    /*!
     * \brief Saves the current scene data (entities and components) to a file.
     *
     * Serializes the scene's entities and components and writes them into the file at the filePath.
     */
    void SaveDataToFile();

    /*!
     * \brief Unloads the scene, removing all entities and freeing associated resources.
     */
    void Unload();

    /*!
     * \brief Updates the scene by updating all entities and their components.
     *
     * This function is called in each frame to advance the scene's state.
     */
    void Update();

    /*!
     * \brief Debug function that prints the number of entities and their components in the scene.
     *
     * Useful for tracking how many entities and components are currently active in the scene.
     */
    void DebugPrintEntityCount() const;

    /*!
     * \brief Gets a list of components attached to a given entity.
     * \param entity The entity whose components are being queried.
     * \return A string listing the components attached to the entity.
     */
    std::string GetComponentList(const ECS::Entity& entity) const;

     /*!
      * \brief Gets the current scene's name.
      * \return The name of the scene.
      */
    const std::string& GetCurrentSceneName() const { return sceneName; }

    /*!
     * \brief Checks if the scene is loaded.
     * \return True if the scene is loaded, false otherwise.
     */
    bool IsLoaded() const { return isLoaded; }

    /*!
     * \brief Checks if the entity data for the scene has been loaded.
     * \return True if entity data has been loaded, false otherwise.
     */
    bool IsDataLoaded() const { return isDataLoaded; }

    std::vector<ECS::Entity> GetEntities();

    // FOR M1 PURPOSES

    /*!
     * \brief Populates the scene with entities for demonstration or testing purposes.
     *
     * This function specifically populates the scene with entities and components for Scene3.
     */
    void Scene3_PopulateScene();
    };

}

#endif