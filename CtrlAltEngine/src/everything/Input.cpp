/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Input.cpp
\author 	Sherman Goh Wee Hao
\par    	shermanweehao.goh@digipen.edu
\date   	Oct 02, 2024
\brief		Partial Action Maps and Wrapper of GLFW Function Calls.


\par
		This is my Input System,
		I initialially went to thinking about Game Implementations , 
		thus the Action map.
		But we would need more usable APIs and flexible calls within our engines.
		We would need to consider how the event/messaging systems is to be integrated.
		There is also the case of using window's callback functions .

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "../src/pch.h"
#include "input.h"
#include <sstream>
#include "../Debug/Debugger.h"


//std::unordered_map<std::string, Key> actionMap;
//std::unordered_map<Key, InputState> keyState;

//static class variables
namespace Input {
	double Input_Container::mouse_device_coord[2]{};
}


namespace Input {

	//Input_Container::Input_Container() {}; // dk if I want to initialise anything here.


	void Input_Container::Init_System(GLFWwindow* ptr_window)
	{
		this->currentWindow = ptr_window;

		// not necessary for now.
		//// would need these 3 callbacks for now,
		//// should i have a function when window changes?
		//glfwSetKeyCallback(this->currentWindow, Input_Container::key_cb);  
		//glfwSetMouseButtonCallback(this->currentWindow, Input_Container::mousebutton_cb); 
		//glfwSetCursorPosCallback(this->currentWindow, Input_Container::mousepos_cb); 


		this->Init_Add_Keybind("KEY W", GLFW_KEY_W, Input::Input_Container::PRESS); 
		this->Init_Add_Keybind("KEY A", GLFW_KEY_A, Input::Input_Container::PRESS); 
		this->Init_Add_Keybind("KEY S", GLFW_KEY_S, Input::Input_Container::PRESS);
		this->Init_Add_Keybind("KEY D", GLFW_KEY_D, Input::Input_Container::PRESS);

		this->Init_Add_Keybind("KEY 1", GLFW_KEY_1, Input::Input_Container::PRESS);
		this->Init_Add_Keybind("KEY 2", GLFW_KEY_2, Input::Input_Container::PRESS);

		this->Init_Add_Keybind("KEY SPACE", GLFW_KEY_SPACE, Input::Input_Container::TRIGGER);
		//this->Init_Add_Keybind("MOUSE LEFT", GLFW_MOUSE_BUTTON_LEFT, Input::Input_Container::PRESS);

	}

	void Input_Container::Test_Keybinds()
	{
		this->Action("KEY W");
		this->Action("KEY A"); 
		this->Action("KEY S"); 
		this->Action("KEY D");

		this->Action("KEY SPACE"); 


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
				std::string Input_debug_string = action_name + " action is to occur! \n";

				Logger::LogInfo(Input_debug_string);
				return true; // true means found the action_name
			}

			return false; // false means don't do the action.
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


	bool Input_Container::GetMouseLeft()
	{
		return glfwGetMouseButton(this->currentWindow, GLFW_MOUSE_BUTTON_LEFT);
	}

	bool Input_Container::GetMouseRight()
	{
		return glfwGetMouseButton(this->currentWindow, GLFW_MOUSE_BUTTON_RIGHT);
	}

	void Input_Container::GetMousePosDevice(double& xpos, double& ypos)
	{
		glfwGetCursorPos(this->currentWindow, &xpos, &ypos);
	}


	void Input_Container::Update(GLFWwindow* ptr_window)
	{
		this->UpdateActionState(ptr_window);
		this->GetMousePosDevice(this->mouse_device_coord[0], this->mouse_device_coord[1]);
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


	void Input_Container::Test_Left_Mouse_Button(double dt)
	{
		if (this->GetMouseLeft())
		{
			static double timer = 0.5f;
			if (timer < 0.5) {
				timer += dt;
				return;
			}
			timer -= 0.5;

			GetMousePosDevice(this->mouse_device_coord[0], this->mouse_device_coord[1]);
			std::ostringstream message; 
			message << "Left Mouse is pressed, device position is: ";
			message << std::setprecision(2) << std::to_string(this->mouse_device_coord[0]);
			message << " , ";
			message << std::setprecision(2) << std::to_string(this->mouse_device_coord[1]);
			message << "\n";
			Logger::LogInfo(message.str());
		}

	}


}// end of namespace for Input , Input_container functionality

//
//namespace GraveYard {
//
//
//	namespace Input {
//		/*  _________________________________________________________________________*/
//		/*! key_cb
//
//		@param GLFWwindow*
//		Handle to window that is receiving event
//
//		@param int
//		the keyboard key that was pressed or released
//
//		@parm int
//		Platform-specific scancode of the key
//
//		@parm int
//		GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
//		action will be GLFW_KEY_UNKNOWN if GLFW lacks a key token for it,
//		for example E-mail and Play keys.
//
//		@parm int
//		bit-field describing which modifier keys (shift, alt, control)
//		were held down
//
//		@return none
//
//		This function is called when keyboard buttons are pressed.
//		When the ESC key is pressed, the close flag of the window is set.
//		*/
//		void Input_Container::key_cb(GLFWwindow* pwin, int key, int scancode, int action, int mod) {
//			if (GLFW_PRESS == action) {
//				//#ifdef _DEBUG
//				//			std::cout << "Key pressed" << std::endl;
//				//#endif
//			}
//			else if (GLFW_REPEAT == action) {
//				//#ifdef _DEBUG
//				//			std::cout << "Key repeatedly pressed" << std::endl;
//				//#endif
//			}
//			else if (GLFW_RELEASE == action) {
//				//#ifdef _DEBUG
//				//			std::cout << "Key released" << std::endl;
//				//#endif
//			}
//
//			//if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action) {
//			//	glfwSetWindowShouldClose(pwin, GLFW_TRUE);
//			//}
//		}
//
//		/*  _________________________________________________________________________*/
//		/*! mousebutton_cb
//
//		@param GLFWwindow*
//		Handle to window that is receiving event
//
//		@param int
//		the mouse button that was pressed or released
//		GLFW_MOUSE_BUTTON_LEFT and GLFW_MOUSE_BUTTON_RIGHT specifying left and right
//		mouse buttons are most useful
//
//		@parm int
//		action is either GLFW_PRESS or GLFW_RELEASE
//
//		@parm int
//		bit-field describing which modifier keys (shift, alt, control)
//		were held down
//
//		@return none
//
//		This function is called when mouse buttons are pressed.
//		*/
//		void Input_Container::mousebutton_cb(GLFWwindow* pwin, int button, int action, int mod) {
//			switch (button) {
//			case GLFW_MOUSE_BUTTON_LEFT:
//				//#ifdef _DEBUG
//				//			std::cout << "Left mouse button ";
//				//#endif
//				break;
//			case GLFW_MOUSE_BUTTON_RIGHT:
//				//#ifdef _DEBUG
//				//			std::cout << "Right mouse button ";
//				//#endif
//				break;
//			}
//			switch (action) {
//			case GLFW_PRESS:
//				//#ifdef _DEBUG
//				//			std::cout << "pressed!!!" << std::endl;
//				//#endif
//				break;
//			case GLFW_RELEASE:
//				//#ifdef _DEBUG
//				//			std::cout << "released!!!" << std::endl;
//				//#endif
//				break;
//			}
//		}
//
//		/*  _________________________________________________________________________*/
//		/*! mousepos_cb
//
//		@param GLFWwindow*
//		Handle to window that is receiving event
//
//		@param double
//		new cursor x-coordinate, relative to the left edge of the client area
//
//		@param double
//		new cursor y-coordinate, relative to the top edge of the client area
//
//		@return none
//
//		This functions receives the cursor position, measured in screen coordinates but
//		relative to the top-left corner of the window client area.
//		*/
//		void Input_Container::mousepos_cb(GLFWwindow* pwin, double xpos, double ypos) {
//			//#ifdef _DEBUG
//			//		std::cout << "Mouse cursor position: (" << xpos << ", " << ypos << ")" << std::endl;
//			//#endif
//
//			Input_Container::mouse_device_coord[0] = (float)xpos;
//			Input_Container::mouse_device_coord[1] = (float)ypos;
//
//		}
//	}// end of namespace for callback functions
//}

