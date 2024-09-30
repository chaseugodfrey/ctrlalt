#ifndef SCENE_H
#define SCENE_H

#include "../Components/CTransform.h"
#include "../Components/CRigidBody.h"
#include "../Systems/SMovement.h"
#include "../Engine/Engine.h"
#include "../ECS/ECS.h"
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Scene {

    class Scene {
    private:
        ECS::Registry* registry;
        std::vector<ECS::Entity> sceneEntities;
        std::string sceneName;
        bool isLoaded;

    public:
        Scene(ECS::Registry* reg) : registry(reg), isLoaded(false) {}

        void LoadFromFile(const std::string& filePath) {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                std::cerr << "Failed to open file: " << filePath << std::endl;
                return;
            }

            sceneEntities.clear();

            std::string keyword;
            int entityCount = 0;

            file >> keyword >> entityCount;
            if (keyword != "Entities:") {
                std::cerr << "Invalid format in file: " << filePath << std::endl;
                return;
            }

            for (int i = 0; i < entityCount; ++i) {
                int id;
                float posX, posY, scaleX, scaleY, rotation;

                file >> keyword >> id;
                file >> keyword >> posX >> keyword >> posY;
                file >> keyword >> scaleX >> keyword >> scaleY;
                file >> keyword >> rotation;

                ECS::Entity entity = registry->CreateEntity();
                entity.AddComponent<Component::CTransform>(
                    glm::vec2(posX, posY),
                    glm::vec2(scaleX, scaleY),
                    rotation
                );
                entity.AddComponent<Component::CRigidBody>(glm::vec2(0, 0));

                sceneEntities.push_back(entity);
            }

            file.close();
            std::cout << "Loaded " << entityCount << " entities from " << filePath << std::endl;
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
                //TODO
            }
        }
    };

} // namespace Scene

#endif // SCENE_H