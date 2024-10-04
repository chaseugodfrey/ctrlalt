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

	/**
	 * @brief Interface for all components
	 * 
	 * @note
	 * Templates allow us to get a unique component ID whenever we create a new component type.
	 * This is done by incrementing a static variable componentID every time a new component is created.
	 * Instead of creating a new component instance every time we call RequireComponent, we only want to check if the component exists in the entity's signature.
	 * We save memory this way in case we don't end up using it. 
	 */
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
	// Entites are only IDs
		EntityID id;

	public:
		//Constructor
		/**
		 * @brief Construct a new Entity object
		 * 
		 * @param id The entity ID
		 * @param registry The entity's registry
		 * 
		 * @note
		 * The entity ID is unique and is used to identify the entity.
		 * The registry is a pointer to the entity's registry.
		 * @see 
		 * Registry
		 */
        Entity(EntityID id) : id(id), registry(nullptr) { 0; }

		/**
		 * @brief Get the ID of the entity
		 * @return id The entity's ID
		 */
		EntityID GetID() const { return id; }

		/**
		 * @brief Copy constructor
		 * @param other The entity to copy
		 * 
		 * @note this is set to default because we only need to copy the entity's ID
		 * no deep copying needed!
		 */
		Entity(const Entity& other) = default;


		//Operator overloads
		/**
		 * @brief Assignment operator
		 * @param other The entity to assign
		 * 
		 * @return Entity& The entity assigned
		 * 
		 * @note follows the copy swap idiom, returns the data that the entity was assigned to
		 */
		Entity operator =(const Entity& other) { id = other.id; return *this; } //follows copy and swap idiom

		/**
		 * @brief Equality operator
		 * 
		 * @param other The entity to compare
		 * 
		 * @return true if the entities are equal
		 * 
		 * @note compares the entity's IDs
		 */
		bool operator == (const Entity& other) const {return id == other.id;}

		/**
		 * @brief Inequality operator
		 * 
		 * @param other The entity to compare
		 * 
		 * @return true if the entities are not equal
		 * 
		 * @note compares the entity's IDs
		 */
		bool operator != (const Entity& other) const {return id != other.id;}

		/**
		 * @brief Greater than operator
		 * 
		 * @param other The entity to compare
		 * 
		 * @return true if the entity's ID is greater than the other entity's ID
		 * 
		 * @see
		 */
		bool operator > (const Entity& other) const {return id > other.id;}

		
		/**
		 * @brief Lesser than operator
		 * 
		 * @param other The entity to compare
		 * 
		 * @return true if the entity's ID is lesser than the other entity's ID
		 * 
		 * @see
		 */
		bool operator < (const Entity& other) const {return id < other.id;}

		
		/**
		 * @brief Greater than or equal to operator
		 * 
		 * @param other The entity to compare
		 * 
		 * @return true if the entity's ID is greater than or equal to the other entity's ID
		 * 
		 * @see
		 */
		bool operator >= (const Entity& other) const {return id >= other.id;}

		/**
		 * @brief Smaller than or equal to operator
		 * 
		 * @param other The entity to compare
		 * 
		 * @return true if the entity's ID is smaller than or equal to the other entity's ID
		 * 
		 * @see
		 */
		bool operator <= (const Entity& other) const {return id <= other.id;}

		/**
		 * @brief Add a component to this entity
		 * @tparam TComponen, the type of component to add to the entity
		 * @tparam ...TArgs type of arguments to pass to the component
		 * @param ...args The arguments to pass to the component
		 * 
		 * @note variadic template function that adds a component to the entity
		 */
		template <typename TComponent, typename ...TArgs> void AddComponent(TArgs&& ...args);

		/**
		 * @brief Remove a component from this entity
		 * @tparam TComponent The type of component to remove from the entity
		 * 
		 * @note removes a component from the entity
		 */
		template <typename TComponent> void RemoveComponent();

		/**
		 * @brief Check if the entity has a component
		 * 
		 * @tparam TComponent The type of component to check for
		 * @return bool true if the entity has the component
		 * 
		 * @note checks if the entity has a component
		 */
		template <typename TComponent> bool HasComponent() const;

		/**
		 * 
		 * @brief Get the component from the entity
		 * 
		 * @tparam TComponent The type of component to get
		 * @return TComponent& The component
		 * 
		 * @note gets the component from the entity
		 */
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

		//System Management
		//Add and remove entities from the system
		void AddEntity(Entity entity);
		void RemoveEntity(Entity entity);
		
		//Completely clear the system of all entities
		void ClearEntities();

		//Get the entities in the system
		std::vector<Entity> GetEntities() const;

		//Get the component mask of the system
		const ComponentMask& GetComponentMask() const;

		//Set the component mask of the system
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
		/**
		 * @brief Construct a new Pool object
		 * @param capacity Initial capacity of the pool (default is 100)
		 */
		Pool(int capacity = 100)
		{
			size = 0;
			data.reserve(capacity);
		}	

		/**
		 * @brief Check if the pool is empty
		 * @return true if the pool is empty
		 * 
		 */
		bool IsEmpty() const {
			return size == 0;
		}

		/**
		 * @brief Get the size of the pool
		 * @return NumEntities The size of the pool
		 * 
		 */
		NumEntities GetSize() const {
			return size;
		}

		/**
		 * @brief Add a component to the pool
		 * @param component The component to add
		 */
		void AddComponent(T component) {
			data.push_back(component);
		}

		/**
		 * @brief Remove component at the specified index
		 * @param the index of the component to remove
		 */
		void RemoveComponent(int index) {
			data.erase(data.begin() + index);
		}

		/**
		 * @brief Get the data in the pool
		 */
		const std::vector<T>& GetData() const {
			return data;
		}

		/**
		 * @brief Get the data in the pool
		 * @param index to the entity ID
		 * @return T& A reference to the component and the specific index
		 */
		T& operator[](EntityID index) {
			return data[index];
		}

		/**
		 * @brief const overload of above fn
		 */
		const T& operator[](EntityID index) const {
			return data[index];
		}

		/**
		 * @brief Resize the pool
		 * @param _size The new size of the pool
		 */
		void Resize(int _size) {
			data.resize(_size);
		}

		/**
		 * @brief Clear the pool
		 */
		void Clear() {
			size = 0;
		}


		/**
		 * @brief Set the component at the specified index
		 * @param index The index to set the component
		 * @param component The component to set
		 * 
		 */
		void SetComponent(EntityID index, T component) {
			data[index] = component;
			size++;
		}

		/**
		 * @brief
		 * Get the component at the specific index
		 * @param index The index to get the component
		 * @return T& The component at the index
		 * @note we typecast the data at the index to the component type
		 */
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

    /**
     * @brief Add a system to the registry
     * @tparam TSystem Type of the system to add
     * @tparam ...TArgs Types of the arguments to forward to the system constructor
     * @param ...args Arguments to forward to the system constructor
     */
	template <typename TSystem, typename ...TArgs> void Registry::AddSystem(TArgs&&  ...args)
	{
		std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
		systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
	}
	
	/**
     * @brief Remove a system from the registry
     * @tparam TSystem Type of the system to remove
     */
	template <typename TSystem> 
	void Registry::RemoveSystem()
	{
		systems.erase(systems.find(std::type_index(typeid(TSystem))));
	}

    /**
     * @brief Check if a system exists in the registry
     * @tparam TSystem Type of the system to check for
     * @return true if the system exists, false otherwise
     */
	template <typename TSystem> 
	bool Registry::HasSystem() const
	{
		return systems.find(std::type_index(typeid(TSystem))) != systems.end();
	}

	/**
     * @brief Get a reference to a system
     * @tparam TSystem Type of the system to get
     * @return TSystem& Reference to the system
     */
	template <typename TSystem> 
	TSystem& Registry::GetSystem() const
	{
		auto system = systems.find(std::type_index(typeid(TSystem)));
		return *(std::static_pointer_cast<TSystem>(system->second));
	}

    /**
     * @brief Add a component to this entity
     * @tparam TComponent Type of the component to add
     * @tparam ...TArgs Types of the arguments to forward to the component constructor
     * @param ...args Arguments to forward to the component constructor
     */
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

	/**
	 * @brief Remove a component from the entity
	 * @tparam TComponent The type of component to remove from the entity
	 * @note removes a component from the entity
	 * 
	 */
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
	/**
	 * @brief Check if the entity has a component
	 * @tparam TComponent The type of component to check for
	 * @return bool true if the entity has the component
	 */
	template <typename TComponent>
	bool Registry::HasComponent(Entity entity) const
	{
		const ComponentID componentID = Component<TComponent>::GetId();
		const EntityID entityID = entity.GetID();

		return entityComponentMasks[entityID].test(componentID);
	}

	/**
	 * @brief Get the component from the entity
	 * @tparam TComponent The type of component to get
	 * @return TComponent& The component
	 * @note gets the component from the entity
	 * Casts the component pool to the correct type and gets the component from the pool
	 */
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

	/**
	 * @brief Add a component to the entity
	 * @tparam TComponent The type of component to add to the entity
	 * @tparam ...TArgs The type of arguments to pass to the component
	 * @param ...args The arguments to pass to the component
	 * @note variadic template function that adds a component to the entity
	 */
	template <typename TComponent, typename ...TArgs>
	void Entity::AddComponent(TArgs&& ...args)
	{
		registry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
	}

	/**
	 * @brief Remove a component from the entity
	 * @tparam TComponent The type of component to remove from the entity
	 * @note removes a component from the entity
	 * 
	 */
	template <typename TComponent> 
	void Entity::RemoveComponent()
	{
		registry->RemoveComponent<TComponent>(*this);
	}

	/**
	 * @brief Check if the entity has a component
	 * @tparam TComponent The type of component to check for
	 * @return bool true if the entity has the component
	 */
	template <typename TComponent> 
	bool Entity::HasComponent() const
	{
		return registry->HasComponent<TComponent>(*this);
	}

	/**
	 * @brief Get the component from the entity
	 * @tparam TComponent The type of component to get
	 * @return TComponent& The component
	 * @note gets the component from the entity
	 */
	template <typename TComponent>
	TComponent& Entity::GetComponent() const
	{
		return registry->GetComponent<TComponent>(*this);
	}

}

#endif
