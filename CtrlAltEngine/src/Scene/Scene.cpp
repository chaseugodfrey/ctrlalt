#include "Scene.h"
#include "../Engine/Engine.h"
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <iostream>

namespace Scene {

	Scene::Scene(ECS::Registry* reg) : registry(reg) {}
	Scene::~Scene() {}


	//void Scene::Init() {
	//	registry->AddSystem<System::SMovement>();

	//	// TESTING PURPOSES
	//	
	//	ECS::Entity E_Player = registry->CreateEntity();
	//	ECS::Entity E_RabbitWhite = registry->CreateEntity();
	//	ECS::Entity E_RabbitBlack = registry->CreateEntity();

	//	// entity creation
	//	// read from file
	//	// get how many entities to create
	//	// for each entity
	//	//         - create entity()
	//	//         - add component() transform -> read transform values
	//	//         - add component() transform -> read rigidbody values


	//	E_Player.AddComponent<Component::CTransform>(glm::vec2(10.0, 30.0), glm::vec2(1.0, 1.0), 60.0);
	//	E_Player.AddComponent<Component::CRigidBody>(glm::vec2(10.0, 30.0));
	//}

    void Scene::Init() {
        registry->AddSystem<System::SMovement>();
        std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
        std::string filePath = "Assets/scene1.txt";  // Your file path
        std::cout << "Attempting to open file at: " << filePath << std::endl;
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Failed to open file!" << std::endl;
            return;
        }

        // Read the "Entities:" keyword and entity count
        std::string keyword;
        int entityCount = 0;

        file >> keyword; // Extract the "Entities:" keyword
        if (keyword != "Entities:") {
            std::cerr << "Invalid format!" << std::endl;
            return;
        }

        file >> entityCount; // Extract the number of entities

        for (int i = 0; i < entityCount; ++i) {
            int id;
            float posX, posY, scaleX, scaleY, rotation;

            // Read and validate entity data
            file >> keyword >> id;           // Expecting "ID: <id>"
            if (keyword != "ID:") {
                std::cerr << "Invalid format for ID!" << std::endl;
                return;
            }

            file >> keyword >> posX;         // Expecting "PosX: <posX>"
            if (keyword != "PosX:") {
                std::cerr << "Invalid format for PosX!" << std::endl;
                return;
            }

            file >> keyword >> posY;         // Expecting "PosY: <posY>"
            if (keyword != "PosY:") {
                std::cerr << "Invalid format for PosY!" << std::endl;
                return;
            }

            file >> keyword >> scaleX;       // Expecting "ScaleX: <scaleX>"
            if (keyword != "ScaleX:") {
                std::cerr << "Invalid format for ScaleX!" << std::endl;
                return;
            }

            file >> keyword >> scaleY;       // Expecting "ScaleY: <scaleY>"
            if (keyword != "ScaleY:") {
                std::cerr << "Invalid format for ScaleY!" << std::endl;
                return;
            }

            file >> keyword >> rotation;     // Expecting "Rot: <rotation>"
            if (keyword != "Rot:") {
                std::cerr << "Invalid format for Rot!" << std::endl;
                return;
            }

            // Create entity
            ECS::Entity entity = registry->CreateEntity();

            // Add Transform component
            entity.AddComponent<Component::CTransform>(
                glm::vec2(posX, posY),
                glm::vec2(scaleX, scaleY),
                rotation
            );

            // Add RigidBody component
            entity.AddComponent<Component::CRigidBody>(glm::vec2(posX, posY));

            std::cout << "ID: " << id << std::endl
                << "Pos X: " << posX << std::endl
                << "Pos Y: " << posY << std::endl
                << "ScaleX: " << scaleX << std::endl
                << "ScaleY: " << scaleY << std::endl;
        }

        file.close();
    }

	
	void Scene::Update() {
	
	}
}