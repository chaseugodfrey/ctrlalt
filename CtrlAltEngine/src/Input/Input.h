#ifndef INPUT_H
#define INPUT_H

#include <unordered_map>
#include <string>
#include "../Engine/Engine.h"


//design Key class.
using Key = int; // may convert to string.

namespace Input {


	class Input_Container {
		struct KeyData;
		//could add a boolean


	public:
		enum InputState;

		Input_Container() = default; // dk if I want to initialise anything here.

		void Init_System(GLFWwindow*);

		//member helper function
		// initialise key bind
		void Init_Add_Keybind(std::string, Key, InputState);

		bool ChangeKeyID(std::string, Key);

		bool ChangeKeyState(std::string, InputState);

		//get result 
		bool Action(std::string);

		// update loop 
		void UpdateActionState(GLFWwindow*);

		bool GetKeyDown(Key);

		//bool GetKeyTriggered(Key);  // if i want to use the glfw callback , I will a messaging system.

		bool GetKeyReleased(Key);


		// a wrapper for GetKeyState -- WINAPI

		//ooo I want more special keystates, but it could do more of game logic.

		//design InputState
		enum InputState {
			RELEASE = GLFW_RELEASE,
			PRESS = GLFW_PRESS,
			REPEAT = GLFW_REPEAT,
			TRIGGER // trigger turns ready when GLFW_RELEASE then can be triggered again.
			// TOGGLE

		};


	private:


		struct KeyData {
			Key keyID;
			InputState keyState;
			bool actionState;
			bool keyStatePrev; // or this can be a secondary boolean    // true pressed, // false released.
		};

		// data members, allow for binding keys.
		// for Key we still have to use GLFW Marcos which is int.
		// I may want to make it a string, but see how.
		using TKeyData = std::unordered_map<std::string, KeyData>::value_type;
		std::unordered_map<std::string, KeyData> actionMap{};
		//std::unordered_map<Key, InputState> keyState{};  // this is for the updating to callback. 

		GLFWwindow* currentWindow{};


		// or I can combine Key and InputState to be like a pair or a struct.
		// when I talk to the GLFW call back, I will just update the keyState.


	};// end of container.

	class Mouse {
		float device_coord[2];


	};

	


}// end of Input Namespace

#endif// end of INPUT_H