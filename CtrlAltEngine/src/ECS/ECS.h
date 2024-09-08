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
//The type_index class is a wrapper class around a std::type_info object, 
// that can be used as index in associative and unordered associative containers.
#include <typeindex>

namespace ECS
{
	/*
	* Defines 
	*/
	class Entity;
	using SystemEntities = std::vector<Entity>;
	class Systems;
	using SystemsHashmap = std::unordered_map<std::type_index, Systems*>;

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
		Entity(int id) : id(id) {}
		int GetID() const { return id; }

		//Operator overloads
		Entity operator =(const Entity& other) {
			id = other.id;
			return *this;
		}

		bool operator == (const Entity& other) const {
			return id == other.id;
		}
		bool operator != (const Entity& other) const {
			return id != other.id;
		}
		bool operator > (const Entity& other) const {
			return id > other.id;
		}
		bool operator < (const Entity& other) const {
			return id < other.id;
		}
		bool operator >= (const Entity& other) const {
			return id >= other.id;
		}
		bool operator <= (const Entity& other) const {
			return id <= other.id;
		}
	};




	/******************************************************************************/
	/*!
	/// System Class
	*/
	/******************************************************************************/
	class System {
	private:
		ComponentSignature componentSignature;
		SystemEntities entities;

	public:
		System() = default;
		~System() = default;

		void AddEntity(Entity entity);
		void RemoveEntity(Entity entity);
		std::vector<Entity> GetEntities() const;
		const ComponentSignature& GetSignature() const;
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
		componentSignature.set(componentID);
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

	public:
		virtual ~Pool() = default;

		Pool(int size = 100)
		{
			data.reserve(size);
		}	

		bool isEmpty() const {
			return data.empty();
		}

		int GetSize() const {
			return data.size();
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

		T& operator[](unsigned int index) {
			return data[index];
		}

		const T& operator[](int index) const {
			return data[index];
		}

		void Resize(int size) {
			data.resize(size);
		}

		void Clear() {
			data.clear();
		}

		void Reserve(int size) {
			data.reserve(size);
		}

		void ShrinkToFit() {
			data.shrink_to_fit();
		}

		void SetComponent(int index, T component) {
			data[index] = component;
		}

		T& GetComponent(int index) {
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
		numEntities numEntities = 0;

		//Each pool contains data for a specific component type
		std::vector<InterfacePool*> componentPools;

		//The signature will let us know which components an entity has
		SignatureMasks entityComponentMasks;

		SystemsHashmap systems;

	public:
		//Registry() = default;
		//~Registry() = default;

		////Entity functions
		//Entity CreateEntity();
		//void DestroyEntity(Entity entity);

		////Component functions
		//template <typename T> void RegisterComponent();
		//template <typename T> void AddComponent(Entity entity, T component);
		//template <typename T> void RemoveComponent(Entity entity);
		//template <typename T> T& GetComponent(Entity entity);

		////System functions
		//template <typename T> void RegisterSystem();
		//template <typename T> void AddEntityToSystem(Entity entity);
		//template <typename T> void RemoveEntityFromSystem(Entity entity);
		//template <typename T> std::vector<Entity> GetEntitiesFromSystem();

	};

}

#endif
