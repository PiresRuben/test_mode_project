#pragma once
#include <GLFW/glfw3.h>

enum class KeyRepresentation {
    Space = GLFW_KEY_SPACE,
    Escape = GLFW_KEY_ESCAPE,
    Enter = GLFW_KEY_ENTER,
	Backspace = GLFW_KEY_BACKSPACE,
	Tab = GLFW_KEY_TAB,
};

enum class KeyReturn {
	Pressed = GLFW_PRESS,
	Released = GLFW_RELEASE,
	Repeat = GLFW_REPEAT
};

enum class MouseButtonRepresentation {
    Left = GLFW_MOUSE_BUTTON_LEFT,
    Right = GLFW_MOUSE_BUTTON_RIGHT,
    Middle = GLFW_MOUSE_BUTTON_MIDDLE
};