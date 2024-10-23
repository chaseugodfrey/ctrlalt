/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Input.h
\author 	Sherman Goh Wee Hao
\par    	shermanweehao.goh@digipen.edu
\date   	Oct 02, 2024
\brief		Partial Action Maps and Wrapper of GLFW Function Calls.


Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef INPUT_H
#define INPUT_H

#include <unordered_map>
#include <string>
#include "../Engine/Engine.h"


//design Key class.
using Key = int; // may convert to string.

namespace Input {


	class Input_Container {
		struct KeyData; // forward delcaration
	


	public:
		
		/// <summary>
		/// Enums for me to create unique InputStates ,
		/// wanted to have Toggle.
		/// </summary>
		enum InputState {
			RELEASE = GLFW_RELEASE,
			PRESS = GLFW_PRESS,
			REPEAT = GLFW_REPEAT,
			TRIGGER // trigger turns ready when GLFW_RELEASE then can be triggered again.
			// TOGGLE

		};

		/// <summary>
		/// To clear the error of not having a constructor
		/// </summary>
		Input_Container() = default; // dk if I want to initialise anything here.

		/// <summary>
		/// Init_System will be in Engine's Load for the specific Actions keys needed.
		/// It will push in the Actions with its Keybinds.
		/// Data is stored in that specific instance.  
		/// </summary>
		/// <param name="GLFWwindow*"></param>
		/// The tentative context you want the keys to take updates from.
		void Init_System(GLFWwindow*);


		
		
		/// <summary>
		/// member helper function
		/// initialise key bind with the various params
		/// </summary>
		/// <param name="std::string"></param>
		/// action name to refer it as.
		/// <param name="Key"></param>
		/// GLFW marcos.
		/// <param name="InputState"></param>
		/// enum mentioned above.
		void Init_Add_Keybind(std::string, Key, InputState);

		/// <summary>
		/// This would be used in Key settings.
		/// The key state would remain
		/// </summary>
		/// <param name="std::string"></param>
		/// The name of the actions
		/// <param name="Key"></param>
		/// GLFW Marco
		/// <returns></returns>
		/// return value is a success or failure.
		bool ChangeKeyID(std::string, Key);

		/// <summary>
		/// This is to change Key State, perhaps when game logic changes it.
		/// </summary>
		/// <param name="std::string"></param>
		/// The name of the actions
		/// <param name="InputState"></param>
		/// The various states.
		/// <returns></returns>
		/// return value is a success or failure.
		bool ChangeKeyState(std::string, InputState);

		//get result 

		/// <summary>
		/// This is the function to call to get the condition to do that Action.
		/// </summary>
		/// <param name="std::string"></param>
		/// The name of the actions
		/// <returns></returns>
		/// return value is to-do or not to-do.
		bool Action(std::string);


		/// <summary>
		/// This is the update loop in the engine , ProcessInput()
		/// </summary>
		/// <param name="GLFWwindow*"></param>
		/// potential changing of the context where we move from editor and 
		/// game view context.
		void Update(GLFWwindow*);

		/// <summary>
		/// This is the update function to loop through the map of Keys.
		/// It does save various info like prevDataState.
		/// I may want to add timers (to key inputs) but that would be more game logic.
		/// </summary>
		/// <param name="GLFWwindow*"></param>
		/// Will use the current windows in *this data.
		void UpdateActionState(GLFWwindow*);

		// calling function.

		/// <summary>
		/// This is a wrapper function to GLFW function call.
		/// </summary>
		/// <param name="Key"></param>
		/// GLFW Macros
		/// <returns></returns>
		/// return true, key down, and false, key is released.
		bool GetKeyDown(Key);

		//bool GetKeyTriggered(Key);  // if i want to use the glfw callback , It will be a messaging system.

		/// <summary>
		/// This is a wrapper function to GLFW function call.
		/// </summary>
		/// <param name="Key"></param>
		/// GLFW Macros
		/// <returns></returns>
		/// return true, key released, and false, key is down.
		bool GetKeyReleased(Key);

		/// <summary>
		/// This is a wrapper function to GLFW function call.
		/// </summary>
		/// <returns></returns>
		/// return true, left mouse is pressed, and false, is released.
		bool GetMouseLeft();

		/// <summary>
		/// This is a wrapper function to GLFW function call.
		/// </summary>
		/// <returns></returns>
		/// return true, right mouse is pressed, and right, is released.
		bool GetMouseRight();

		/// <summary>
		/// This is a wrapper function to GLFW function call.
		/// </summary>
		/// <param name="xpos"></param>
		/// device coord, bad implementation
		/// <param name="ypos"></param>
		/// device coord, bad implementation
		void GetMousePosDevice(double& xpos, double& ypos);  


		/// <summary>
		/// Wrapped the test case for M1 submissions for key inputs.
		/// </summary>
		/// <param name="dt"></param>
		/// delta time from Debug namespace
		void Test_Left_Mouse_Button(double dt);

		/// <summary>
		/// Wrapped the test case for M1 submissions for mouse inputs.
		/// </summary>
		void Test_Keybinds();


		// a wrapper for GetKeyState -- WINAPI

		//ooo I want more special keystates, but it could do more of game logic.

		


	private:

		//static void key_cb(GLFWwindow* pwin, int key, int scancode, int action, int mod); 
		//static void mousebutton_cb(GLFWwindow* pwin, int button, int action, int mod);
		//static void mousepos_cb(GLFWwindow* pwin, double xpos, double ypos);


		/// <summary>
		/// This is my attempt at tracking relevant informations for Keys.
		/// I believe that the GLFW callbacks may do a better job.
		/// </summary>
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
		

		GLFWwindow* currentWindow{}; // saved window ptr to Input_Container

		// data for mouse.
		static double mouse_device_coord[2]; // mouse.


		// or I can combine Key and InputState to be like a pair or a struct.
		// when I talk to the GLFW call back, I will just update the keyState.


	};// end of container.

	// better to make lump with the Input_Container.
	//class Mouse {
	// // Mouse states keyID are GLFW_MOUSE_BUTTON_LEFT and GLFW_MOUSE_BUTTON_RIGHT
	//	float device_coord[2];
	//};

	
	


}// end of Input Namespace

#endif// end of INPUT_H