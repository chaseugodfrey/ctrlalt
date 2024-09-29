#ifndef SCENE_H
#define SCENE_H

#include "../Components/CTransform.h"
#include "../Components/CRigidBody.h"
#include "../Systems/SMovement.h"
#include "../Engine/Engine.h"
#include "../ECS/ECS.h"

namespace Scene{

	class Scene {

	private:
		//std::vector<ECS::Registry*> registries;	//To store all Scene data
		ECS::Registry* registry;				//To store 1 Scene data
		std::vector<std::string> scenePaths{"Assets/scene1.txt", 
											"Assets/scene2.txt", 
											"Assets/scene3.txt"};

	public:
		Scene(ECS::Registry*);
		~Scene();

		void Init();
		void Update();

	};
}




#endif