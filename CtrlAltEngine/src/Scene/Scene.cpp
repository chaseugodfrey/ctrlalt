#include "Scene.h"
#include "../Engine/Engine.h"

namespace Scene {

	Scene::Scene(ECS::Registry* reg) : registry(reg) {}
	Scene::~Scene() {}


	void Scene::Init() {
		registry->AddSystem<System::SMovement>();
		
		ECS::Entity E_Player = registry->CreateEntity();
		ECS::Entity E_RabbitWhite = registry->CreateEntity();
		ECS::Entity E_RabbitBlack = registry->CreateEntity();

		E_Player.AddComponent<Component::CTransform>(glm::vec2(10.0, 30.0), glm::vec2(1.0, 1.0), 60.0);
		E_Player.AddComponent<Component::CRigidBody>(glm::vec2(10.0, 30.0));
	}
	
	void Scene::Update() {}
}