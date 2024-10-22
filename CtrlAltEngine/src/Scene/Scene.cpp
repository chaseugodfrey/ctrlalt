/**
@group CTRL ALT
@file Scene.cpp
@brief Implementation of the Scene
Created by Chase Rodrigues
rodrigues.i@digipen.edu
*/
#include "Scene.h"

// INCLUDES
// =========================================================================================================
#include "../Components/CRigidBody.h"
#include "../Components/CTransform.h"
#include "../Components/CIdentifier.h"
#include "../Components/CCollider.h"
#include "../Render/Render.h"


namespace Scene {

    void Scene::RegisterComponentDeserializers() {
        RegisterComponentDeserializer<Component::CTransform>("CTransform",
            [](ECS::Entity& entity, std::istream& is) {
                float posX, posY, scaleX, scaleY, rotation;
                is >> posX >> posY >> scaleX >> scaleY >> rotation;
                entity.AddComponent<Component::CTransform>(
                    vec2(posX, posY),
                    vec2(scaleX, scaleY),
                    rotation
                );
                Logger::LogInfo("CTransform component added");
            });

        RegisterComponentDeserializer<Component::CRigidBody>("CRigidBody",
            [](ECS::Entity& entity, std::istream& is) {
                float velX, velY;
                is >> velX >> velY;
                entity.AddComponent<Component::CRigidBody>(vec2(velX, velY));
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


    void Scene::CreateEntity(const std::string& entityType)
    {
        std::map<std::string, std::string> componentData;

        std::size_t entityID = GetNextEntityID();

        if (entityType == "Basic")
        {
            ECS::Entity entity = entityFactory.CreateBasicEntity();
            componentData["CTransform"] = SerializeTransform(entity.GetComponent<Component::CTransform>());
            sceneEntities.push_back(entity);
            entityData.push_back({ std::to_string(entityID), componentData });
            //    registry->AddEntityToSystems(entity);
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

    void Scene::LoadEntityData() {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            return;
        }

        entityData.clear();

        std::string line;
        int entityCount;
        file >> entityCount;
        std::getline(file, line); // Consume the newline

        for (int i = 0; i < entityCount; ++i) {
            std::string entityId;
            file >> line >> entityId;
            std::getline(file, line); // Consume the newline

            std::map<std::string, std::string> componentData;

            while (std::getline(file, line) && !line.empty()) {
                std::istringstream iss(line);
                std::string componentType;
                iss >> componentType;
                std::string data = line.substr(componentType.length() + 1); // +1 for the space
                componentData[componentType] = data;
            }

            entityData.push_back({ entityId, componentData });
            nextEntityID = std::max(nextEntityID, std::stoull(entityId) + 1);
        }

        file.close();
        Logger::LogInfo("Loaded data for " + std::to_string(entityData.size()) + " entities from " + filePath);
    }

    void Scene::Load() {
        if (isLoaded) {
            Logger::LogInfo("Scene already loaded: " + sceneName);
            return;
        }

        for (const auto& [entityId, components] : entityData) {
            ECS::Entity entity = registry->CreateEntity();
            //Updating in scene does not imply updating in Registry

            for (const auto& [componentType, componentData] : components) {
                auto it = componentDeserializers.find(componentType);
                if (it != componentDeserializers.end()) {
                    std::istringstream iss(componentData);
                    it->second(entity, iss); // this updates component data
                }
                else {
                    Logger::LogInfo("Unknown component type: " + componentType);
                }
            }

            entity.AddComponent<Render::CRenderable>();
            Render::CRenderable& rComp = entity.GetComponent<Render::CRenderable>();
            rComp.SetTexture("Axol_Sprite");
            entity.AddComponent<Render::CSpriteAnimator>();
            Render::CSpriteAnimator& spriteAnimator = entity.GetComponent<Render::CSpriteAnimator>();
            spriteAnimator.AddAnimation("anim1", Render::SpriteAnimationAsset::CreateSpriteAsset({
                    {0.f,0.5f,0.f,0.5f}, {0.5f,1.f,0.f,0.5f}, 
                    {0.f,0.5f,0.5f,1.f}, {0.5f,1.f,0.5f,1.f} }, 1.f, "Axol_Sprite"));
            spriteAnimator.AddAnimation("anim2", Render::SpriteAnimationAsset::CreateSpriteAsset({
                    {0.f,0.5f,0.f,0.5f}, {0.5f,1.f,0.f,0.5f},
                    {0.f,0.5f,0.5f,1.f}, {0.5f,1.f,0.5f,1.f} }, 0.1f, "test"));
            spriteAnimator.AddTransition("anim1", [](ECS::Entity const& e) -> bool{
                Component::CTransform& tForm = e.GetComponent<Component::CTransform>();
                return tForm.scale.x >= 1.4f;
                }, "anim2");
            spriteAnimator.AddTransition("anim2", [](ECS::Entity const& e) -> bool {
                Component::CTransform& tForm = e.GetComponent<Component::CTransform>();
                return tForm.scale.x <= 0.6f;
                }, "anim1");
            spriteAnimator.SetStartAnimation("anim1");

            sceneEntities.push_back(entity);
            registry->AddEntityToSystems(entity);
        }

   //     registry->Update();
        isLoaded = true;
        Logger::LogInfo("Created " + std::to_string(sceneEntities.size()) + " entities for scene: " + sceneName);
    }

    void Scene::Unload()
    {
        if (!isLoaded) return;

        registry->ClearEntities();
        sceneEntities.clear();
        
        nextEntityID = 0; 

        isLoaded = false;
        Logger::LogInfo("Unloaded scene: " + sceneName);
    }

    void Scene::SaveDataToFile()
    {
        sceneName[0] = static_cast<char>(std::tolower(sceneName[0]));
        std::string _path = "Assets/" + sceneName + ".txt";

        std::ofstream file(_path);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << _path << std::endl;
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
        Logger::LogInfo("Saved " + std::to_string(sceneEntities.size()) + " entities to " + _path);
    }

    std::string Scene::GetComponentList(const ECS::Entity& entity) const {
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

    void Scene::Update()
    {
        // SCENE 1
        // M1 SUBMISSION STUFFS

        if (sceneName == "Scene1")
        {
            // We are spawning bg separately as render component currently has no deserialization functionality
            static bool spawn_bg = false;

            if (!spawn_bg)
            {
                ECS::Entity wireframe_ui = registry->CreateEntity();
                wireframe_ui.AddComponent<Render::CRenderable>();
                Render::CRenderable& rComp2 = wireframe_ui.GetComponent<Render::CRenderable>();
                rComp2.SetColor({ 1.f,0.f,0.f,0.5f });
                sceneEntities.push_back(wireframe_ui);

                // BG
                ECS::Entity bg = registry->CreateEntity();
                bg.AddComponent<Component::CTransform>(MathLib::vec2{0,0}, MathLib::vec2{16.0, 9.0}, 0);
                bg.AddComponent<Render::CRenderable>();
                Render::CRenderable& rComp = bg.GetComponent<Render::CRenderable>();
                rComp.SetTexture("BG_Test");
                rComp.SetRenderLayer(Render::CRenderable::R_BACKGROUND);
                sceneEntities.push_back(bg);
                spawn_bg = true;
            }


            for (auto& ent : sceneEntities)
            {
                auto rComp = ent.GetComponent<Render::CRenderable>();
                if (rComp.GetRenderLayer() == Render::CRenderable::R_BACKGROUND) {
                    continue;
                }
                auto& transf = ent.GetComponent<Component::CTransform>();

                // SCALE UP AND DOWN
                static float swap_scale = 1;
                static MathLib::vec2 scale_speed(0.001, 0.001);
                transf.scale += scale_speed * swap_scale;

                if (transf.scale.x >= 1.5)
                    swap_scale = -1;
                else if (transf.scale.x <= 0.5)
                    swap_scale = 1;
                    
                // CLAMP ROTATION
                transf.rotation += 1.0;
                if (transf.rotation >= 360)
                    transf.rotation = 0;

            }
        }

        else if (sceneName == "Scene2")
        {
            // We are manually adding collider as collider component currently has no deserialization functionality
            static bool add_collider = false;

            if (!add_collider)
            {
                for (auto& ent : sceneEntities)
                {
                    auto& transf = ent.GetComponent<Component::CTransform>();
                    ent.AddComponent<Component::CRigidBody>();
                    ent.AddComponent<Component::AABB>(transf.position, 2.0f, 2.0f);
                }

                auto& rb = sceneEntities[0].GetComponent<Component::CRigidBody>();
                rb.vel = MathLib::vec2(5.0, 0.0);

                add_collider = true;
            }

        }

        else if (sceneName == "Scene3")
        {
            Scene3_PopulateScene();
        }

    }

    void Scene::DebugPrintEntityCount() const
    {
        Logger::LogInfo("Total entities in scene: " + sceneEntities.size());
        for (const auto& entity : sceneEntities) {
            Logger::LogInfo("Entity " + std::to_string(entity.GetID()));
            std::string componentList = GetComponentList(entity);
            Logger::LogInfo("Entity " + std::to_string(entity.GetID()) + " components:" + componentList);
        }
    }

    void Scene::Scene3_PopulateScene()
    {
        static bool spawned = false;
        if (spawned)
            return;

        double max_obj = 2500;
        for (double i = 0.0; i < max_obj; i++)
        {
            //CreateEntity("Basic");
            ECS::Entity axol = registry->CreateEntity();
            axol.AddComponent<Component::CIdentifier>();
            axol.AddComponent<Component::CTransform>(MathLib::vec2((i / max_obj) * 10 - 5, (i / max_obj) * 10 - 5));
            axol.AddComponent<Render::CRenderable>();
            Render::CRenderable& rComp = axol.GetComponent<Render::CRenderable>();
            rComp.SetTexture("Axol_Sprite");
            rComp.SetRenderLayer(Render::CRenderable::R_WORLD);
            sceneEntities.push_back(axol);
            registry->Update();
            
            if (i == max_obj - 1)
                spawned = true;
        }
        Logger::LogInfo("Dynamically created 2500 objects in Scene Runtime for Scene 3.");
    }

    std::vector<ECS::Entity> Scene::GetEntities()
    {
        return sceneEntities;
    }
}