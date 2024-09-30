#pragma once // this will be a graveyard of code.

// these code is done by prof parminder and prof prasanna

#include "gleq.h"

auto eventHandler = [](GLEQevent event) { event_handler_impl(event); };


void event_handler_impl(GLEQevent& event)
{
    switch (event.type)
    {
    case GLEQ_KEY_PRESSED:
    case GLEQ_KEY_RELEASED:
    case GLEQ_KEY_REPEATED: {
        GLApp::key_cb(GLApp::ptr_window, event.keyboard.key,
            event.keyboard.scancode,
            convertGleqToGlfwEvent(event.type),
            event.keyboard.mods);
        break;
    }
    case GLEQ_BUTTON_PRESSED:
    case GLEQ_BUTTON_RELEASED: {
        GLApp::mousebutton_cb(GLApp::ptr_window, event.mouse.button,
            convertGleqToGlfwEvent(event.type),
            event.mouse.mods);
        break;
    }
    case GLEQ_CURSOR_MOVED: {
        GLApp::mousepos_cb(GLApp::ptr_window, event.pos.x, event.pos.y);
        break;
    }
    default:
        break;
    }
}


//nvm
// this is what i wanted

void GLHelper::setup_event_callbacks() {
    AUTOMATION_HOOK_EVENTS(); // Automation hook. [!WARNING!] Do not alter/remove this! 

    glfwSetFramebufferSizeCallback(GLHelper::ptr_window, GLHelper::fbsize_cb);
    glfwSetKeyCallback(GLHelper::ptr_window, GLHelper::key_cb);
    glfwSetMouseButtonCallback(GLHelper::ptr_window, GLHelper::mousebutton_cb);
    glfwSetCursorPosCallback(GLHelper::ptr_window, GLHelper::mousepos_cb);
    glfwSetScrollCallback(GLHelper::ptr_window, GLHelper::mousescroll_cb);
}

void GLApp::key_cb(GLFWwindow* pwin, int key, int scancode, int action, int mod) {
    if (GLFW_PRESS == action) {
#ifdef _DEBUG
        std::cout << "Key pressed" << std::endl;
#endif
    }
    else if (GLFW_REPEAT == action) {
#ifdef _DEBUG
        std::cout << "Key repeatedly pressed" << std::endl;
#endif
    }
    else if (GLFW_RELEASE == action) {
#ifdef _DEBUG
        std::cout << "Key released" << std::endl;
#endif
    }

    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action) {
        glfwSetWindowShouldClose(pwin, GLFW_TRUE);
    }
}

void GLApp::mousebutton_cb(GLFWwindow* pwin, int button, int action, int mod) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
#ifdef _DEBUG
        std::cout << "Left mouse button ";
#endif
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
#ifdef _DEBUG
        std::cout << "Right mouse button ";
#endif
        break;
    }
    switch (action) {
    case GLFW_PRESS:
#ifdef _DEBUG
        std::cout << "pressed!!!" << std::endl;
#endif
        break;
    case GLFW_RELEASE:
#ifdef _DEBUG
        std::cout << "released!!!" << std::endl;
#endif
        break;
    }
}


void GLApp::mousepos_cb(GLFWwindow* pwin, double xpos, double ypos) {
#ifdef _DEBUG
    std::cout << "Mouse cursor position: (" << xpos << ", " << ypos << ")" << std::endl;
#endif
}


void GLApp::mousescroll_cb(GLFWwindow* pwin, double xoffset, double yoffset) {
#ifdef _DEBUG
    std::cout << "Mouse scroll wheel offset: ("
        << xoffset << ", " << yoffset << ")" << std::endl;
#endif
}


void GLApp::error_cb(int error, char const* description) {
    std::cerr << "GLFW error: " << description << std::endl;
}