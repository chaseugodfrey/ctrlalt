#pragma once


	template <typename TComponent>
	void ECS::System::RequireComponent() {
		//Get the component ID from the component type
		const ComponentID componentID = Component<TComponent>::GetId();

		//Set the bit at the component ID to true
		componentSignature.set(componentID);
	}
