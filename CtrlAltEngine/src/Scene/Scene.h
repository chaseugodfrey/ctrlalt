#ifndef SCENE_H
#define SCENE_H

#include "../Components/CTransform.h"
#include "../Components/CRigidBody.h"
#include "../Systems/SMovement.h"
#include "../Engine/Engine.h"
#include "../ECS/ECS.h"
#include <map>
#include <string>

namespace Scene{

	class Scene {

	private:
		ECS::Registry* registry;				//To store 1 Scene data
		std::vector<std::string> scenePaths{"Assets/scene1.txt", 
											"Assets/scene2.txt", 
											"Assets/scene3.txt"};
		std::map<std::string, std::vector<ECS::Entity>> sceneMap; //map contains ALL entity information seperated by filepaths to determine scene

	public:
		Scene(ECS::Registry*);
		~Scene();

		void Init();
		void Update();

	};
}




#endif