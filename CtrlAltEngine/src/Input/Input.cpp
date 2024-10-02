
#include "input.h"


//std::unordered_map<std::string, Key> actionMap;
//std::unordered_map<Key, InputState> keyState;


namespace Input {

	//Input_Container::Input_Container() {}; // dk if I want to initialise anything here.


	void Input_Container::Init_System(GLFWwindow* ptr_window)
	{
		this->currentWindow = ptr_window;


		this->Init_Add_Keybind("KEY W", GLFW_KEY_W, Input::Input_Container::PRESS);
		this->Init_Add_Keybind("KEY A", GLFW_KEY_A, Input::Input_Container::PRESS);
		this->Init_Add_Keybind("KEY S", GLFW_KEY_S, Input::Input_Container::PRESS);
		this->Init_Add_Keybind("KEY D", GLFW_KEY_D, Input::Input_Container::PRESS);

		this->Init_Add_Keybind("KEY 1", GLFW_KEY_1, Input::Input_Container::PRESS);
		this->Init_Add_Keybind("KEY 2", GLFW_KEY_2, Input::Input_Container::PRESS);

		this->Init_Add_Keybind("KEY SPACE", GLFW_KEY_SPACE, Input::Input_Container::TRIGGER);

	}

	//member helper function
	// initialise key bind
	void Input_Container::Init_Add_Keybind(std::string action_name, Key key, InputState keystate)
	{
		// validation of action_name and key


		if (this->actionMap.find(action_name) == this->actionMap.end()) {
			Input_Container::KeyData tmp{ key, keystate };
			this->actionMap.insert(std::pair<std::string, Input_Container::KeyData> {action_name, tmp});
		}
		else {
			//return action_name is already in the map	
				// can return false or output that action have been added.
		}

		// not in use as it is for a messaging system
		//if (this->keyState.find(key) == this->keyState.end()) {
		//	// this will be the containers that I will iterate through to check.
		//	this->keyState.insert(std::pair<Key, InputState>{key, keystate});  
		//}
		//else {
		//	//return key is already in the map to be updated.
		//}



	}// end of Init_Add_Keybind function.



	bool Input_Container::ChangeKeyID(std::string action_name, Key key)
	{
		// validation of key missing .
		// should this be a queue? to be resolved at the end of the loop?

		if (this->actionMap.find(action_name) != this->actionMap.end()) {
			this->actionMap[action_name].keyID = key;
			return true;
		}
		else {
			// no existing action_name in map;
			return false;
		}


	}// end of ChangeKeyID function.

	bool Input_Container::ChangeKeyState(std::string action_name, InputState keystate) 
	{
		// validation of checking keystate.
		// should this be a queue? to be resolved at the end of the loop?
		if (this->actionMap.find(action_name) != this->actionMap.end()) {
			this->actionMap[action_name].keyState = keystate;
			return true;
		}
		else {
			// no existing action_name in map;
			return false;
		}


	}//end of ChangeKeyState function.



	//get result 
	bool Input_Container::Action(std::string action_name)
		// this "do" should be switch on.
	{
		// I find the KeyData.

		// then use the various API calls to check it.
		// does not optimise if the action is checked multiple times in one loop,

		if (this->actionMap.find(action_name) != this->actionMap.end()) { // i want to locate the key.
			if (this->actionMap[action_name].actionState) {
				std::string Input_debug_string = action_name + " is to occur! \n";
				std::cout << Input_debug_string;
			}

			return true; // true means found the action_name
		}
		else {
			// no existing action_name in map;
			return false;  // false means don't have the action_name
		}


	}

	bool Input_Container::GetKeyDown(Key key)
	{
		std::cout << key << " Key is held" << std::endl;
		return glfwGetKey(this->currentWindow, key);
	}

	//bool GetKeyTriggered(Key);  // if i want to use the glfw callback , I will need a messaging system.

	bool Input_Container::GetKeyReleased(Key key)
	{
		std::cout << key << " Key is released" << std::endl;
		return glfwGetKey(this->currentWindow, key);
	}

	//update in glfw callback.
	void Input_Container::UpdateActionState(GLFWwindow* ptr_window)
		// what am I trying to update.
	{
		this->currentWindow = ptr_window; // if we have multiple contexts (?)
		// I think this is my events/ messaging system
		// when the thing is true or false. 

		// do i have a container to store whenever action should be in the true state.

		//for (TKeyData& obj : this->actionMap) {
		//	obj.second.keyID;

		//}
		for (auto& [action_name, key_data] : this->actionMap) {

			switch (key_data.keyState) {
			case InputState::REPEAT:
				// prev keystate was true and current is true.
				if (key_data.keyStatePrev && glfwGetKey(ptr_window, key_data.keyID))
					key_data.actionState = true;
				else
					key_data.actionState = false;
				break;
			case InputState::TRIGGER:
				// prev keystate was false and current is true.
				if (!key_data.keyStatePrev && glfwGetKey(ptr_window, key_data.keyID))
					key_data.actionState = true;
				else
					key_data.actionState = false;
				break;
			default:
				// for PRESS and RELEASED, like a true or false
				key_data.actionState = (glfwGetKey(ptr_window, key_data.keyID) == key_data.keyState);
			}



			key_data.keyStatePrev = (glfwGetKey(ptr_window, key_data.keyID) == GLFW_PRESS);  // this returns an int.
			// what does glfewGetKey return? press or released.


		}// end of ranged for through the map.

	}


}


