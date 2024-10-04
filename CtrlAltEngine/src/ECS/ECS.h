/******************************************************************************/
/*!
\group  	CtrlAlt
\file		ECS.h
\author 	Michael Lazaroo
\par    	m.lazaroo@digipen.edu
\date   	Sep 08, 2024
\brief		ECS Implementation


Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

/// PREPROCESSOR DIRECTIVES
///=========================================================================================================
#ifndef ECS_H
#define ECS_H

// INCLUDES
///=========================================================================================================
#include "Types.h"
#include <unordered_map>
#include <set>
//The type_index class is a wrapper class around a std::type_info object, 
// that can be used as index in associative and unordered associative containers.
#include <typeindex>
#include <memory>
#include "../Logger/Logger.h"

namespace ECS
{
	/*
	* Defines 
	*/
	class Entity;
	using SystemEntities = std::vector<Entity>;
	class System;
	using SystemsHashmap = std::unordered_map < std::type_index, std::shared_ptr<System>> ;

	/******************************************************************************/
	/*!
	/// Component Class
	*/
	/******************************************************************************/

	// Templates allow us to get a unique component ID whenever we create a new component type.
	// This is done by incrementing a static variable componentID every time a new component is created.
	// Instead of creating a new component instance every time we call RequireComponent, we only want to check if the component exists in the entity's signature.
	// We save memory this way in case we don't end up using it.
	template <typename T>
	class Component : public InterfaceComponent{
	public:
		// Returns a unique component ID of Component<T>
		static ComponentID GetId() {
			static ComponentID id = componentID++;
			return id;
		}
	};




	/******************************************************************************/
	/*!
	/// Entity Class
	*/
	/******************************************************************************/
	class Entity {
	private:
		EntityID id;

	public:
		//Constructor
		/*
		
		*/
        Entity(EntityID id) : id(id), registry(nullptr) { 0; }
		EntityID GetID() const { return id; }
		Entity(const Entity& other) = default;


		//Operator overloads
		Entity operator =(const Entity& other) { id = other.id; return *this; } //follows copy and swap idiom

		bool operator == (const Entity& other) const {return id == other.id;}
		bool operator != (const Entity& other) const {return id != other.id;}
		bool operator > (const Entity& other) const {return id > other.id;}
		bool operator < (const Entity& other) const {return id < other.id;}
		bool operator >= (const Entity& other) const {return id >= other.id;}
		bool operator <= (const Entity& other) const {return id <= other.id;}

		template <typename TComponent, typename ...TArgs> void AddComponent(TArgs&& ...args);
		template <typename TComponent> void RemoveComponent();
		template <typename TComponent> bool HasComponent() const;
		template <typename TComponent> TComponent& GetComponent() const;

		// Hold a pointer to the entity's registry
		class Registry* registry;
	};




	/******************************************************************************/
	/*!
	/// System Class
	*/
	/******************************************************************************/
	class System {
	private:
		ComponentMask componentMask;
		SystemEntities entities;

	public:
		System() = default;
		~System() = default;

		void AddEntity(Entity entity);
		void RemoveEntity(Entity entity);
		void ClearEntities();
		std::vector<Entity> GetEntities() const;
		const ComponentMask& GetComponentMask() const;
		template <typename TComponent> void RequireComponent();
	};

	/*
	\fn RequireComponent
	\brief Defines the component signature that an entity requires for the system
	\param TComponent - The component type that the entity requires

	We call RequireComponent using only it's type to derive the correct component ID,
	rather than having an instance of the component at hand.
	This is because we don't want to create a new component instance every time we call RequireComponent.
	We only want to check if the component exists in the entity's signature.
	*/
	template <typename TComponent>
	void System::RequireComponent() {
		//Get the component ID from the component type
		const ComponentID componentID = Component<TComponent>::GetId();

		//Set the bit at the component ID to true
		componentMask.set(componentID);
	}

	/******************************************************************************/
	/*!
	/// Pool Class
	*/
	/******************************************************************************/
	template <typename T>
	class Pool :public InterfacePool {
	private: 
		std::vector<T> data;
		int size;

		std::unordered_map<int, int> entityIDToIndex;
		std::unordered_map<int, int> indexToEntityID;
		// Have to clear some of these functions, as they wont be used for now some are just
		// interfaces to the std::vector functions
	public:
		virtual ~Pool() = default;

		Pool(int capacity = 100)
		{
			size = 0;
			data.reserve(capacity);
		}	

		bool IsEmpty() const {
			return size == 0;
		}

		NumEntities GetSize() const {
			return size;
		}

		void AddComponent(T component) {
			data.push_back(component);
		}

		void RemoveComponent(int index) {
			data.erase(data.begin() + index);
		}

		const std::vector<T>& GetData() const {
			return data;
		}

		T& operator[](EntityID index) {
			return data[index];
		}

		const T& operator[](EntityID index) const {
			return data[index];
		}

		void Resize(int _size) {
			data.resize(_size);
		}

		void Clear() {
			size = 0;
		}

		void SetComponent(EntityID index, T component) {
			data[index] = component;
			size++;
		}

		T& GetComponent(EntityID index) {
			return static_cast<T&>(data[index]);
		}
	};

	/******************************************************************************/
	/*!
	/// Registry Class
	*/
	/******************************************************************************/
	class Registry {
	private:
		//Keeps track of the amount of entities in the world
		NumEntities numEntities = 0;

		//Each pool contains data for a specific component type
		std::vector<std::shared_ptr<InterfacePool>> componentPools;

		//The signature will let us know which components an entity has
		SignatureMasks entityComponentMasks;

		//Map of active systems
		SystemsHashmap systems;

		// Flagged entites that will be removed or added
		std::set<Entity> entitiesAddQueue;
		std::set<Entity> entitiesRemoveQueue;

		std::deque<int> freeIDs;

	public:

		Registry()
		{
			//Logger::LogInfo("Registry created");
		}
		~Registry()
		{
			//Logger::LogInfo("Registry deleted");
		}

		void Update();

		//Entity Management
		Entity CreateEntity();
		void KillEntity(Entity entity);
		void ClearEntities();

		//Component Management
		template <typename TComponent, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);
		template <typename TComponent> void RemoveComponent(Entity entity);
		template <typename TComponent> bool HasComponent(Entity entity)const;
		template <typename TComponent> TComponent& GetComponent(Entity entity) const;

		//System Management
		template <typename TSystem,typename ...TArgs> void AddSystem(TArgs&&  ...args);
		template <typename TSystem> void RemoveSystem();
		template <typename TSystem> bool HasSystem() const;
		template <typename TSystem> TSystem& GetSystem() const;

		void AddEntityToSystems(Entity entity);
		void RemoveEntityFromSystems(Entity entity);
	};

	template <typename TSystem, typename ...TArgs> void Registry::AddSystem(TArgs&&  ...args)
	{
		std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
		systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
	}
	
	template <typename TSystem> 
	void Registry::RemoveSystem()
	{
		systems.erase(systems.find(std::type_index(typeid(TSystem))));
	}

	template <typename TSystem> 
	bool Registry::HasSystem() const
	{
		return systems.find(std::type_index(typeid(TSystem))) != systems.end();
	}

	template <typename TSystem> 
	TSystem& Registry::GetSystem() const
	{
		auto system = systems.find(std::type_index(typeid(TSystem)));
		return *(std::static_pointer_cast<TSystem>(system->second));
	}


	template <typename TComponent, typename ...TArgs>
	void Registry::AddComponent(Entity entity, TArgs&& ...args)
	{
		//Get the component ID from the component type
		const ComponentID componentID = Component<TComponent>::GetId();
		const EntityID entityID = entity.GetID();

		if (componentID >= componentPools.size())
		{
			componentPools.resize(componentID + 1);
		}
		if (!componentPools[componentID])
		{
			std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
			componentPools[componentID] = newComponentPool;
		}

		std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentID]);

		if (entityID >= componentPool->GetSize())
		{
			componentPool->Resize(numEntities);
		}

		TComponent newComponent(std::forward<TArgs>(args)...);

		componentPool->SetComponent(entityID, newComponent);
		entityComponentMasks[entityID].set(componentID);

	}

	template <typename TComponent>
	void Registry::RemoveComponent(Entity entity)
	{
		//Get the component ID from the component type
		const ComponentID componentID = Component<TComponent>::GetId();
		const EntityID entityID = entity.GetID();

		if (componentID >= componentPools.size())
		{
			return;
		}

		if (!componentPools[componentID])
		{
			return;
		}
		std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentID]);
		componentPools->RemoveC(entityID);

		entityComponentMasks[entityID].set(componentID, false);
		//Logger::LogInfo("Component ID: " + std::to_string(componentID) + " was removed from entity ID: " + std::to_string(entityID));
	}

	template <typename TComponent>
	bool Registry::HasComponent(Entity entity) const
	{
		const ComponentID componentID = Component<TComponent>::GetId();
		const EntityID entityID = entity.GetID();

		return entityComponentMasks[entityID].test(componentID);
	}

	template <typename TComponent> TComponent& Registry::GetComponent(Entity entity) const
	{
		const auto componentID = Component<TComponent>::GetId();
		const auto entityID = entity.GetID();
		auto componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentID]);

		return componentPool->GetComponent(entityID);
	}


	//seperation of templated definitions, will do in future
	//#include "ECSTemplates.h"

	/******************************************************************************/
	//Entity Implementation
	/******************************************************************************/

	template <typename TComponent, typename ...TArgs>
	void Entity::AddComponent(TArgs&& ...args)
	{
		registry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
	}

	template <typename TComponent> 
	void Entity::RemoveComponent()
	{
		registry->RemoveComponent<TComponent>(*this);
	}

	template <typename TComponent> 
	bool Entity::HasComponent() const
	{
		return registry->HasComponent<TComponent>(*this);
	}

	template <typename TComponent>
	TComponent& Entity::GetComponent() const
	{
		return registry->GetComponent<TComponent>(*this);
	}

}

#endif
