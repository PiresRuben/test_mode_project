#include <iostream>
#include "Modules/InputManager.hpp"
#include "Engine.hpp"
#include "Modules/Window.hpp"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager() {
    if (instance != nullptr) {
        throw std::runtime_error("InputManager instance already exists!");
    }
    instance = this;
    std::cout << "InputManager created" << std::endl;
}

void InputManager::SetWindow(GLFWwindow* window) {
    this->window = window;

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, CursorPositionCallback);
    glfwSetScrollCallback(window, ScrollCallback);
}

void InputManager::Init() {
    std::cout << "InputManager initializing" << std::endl;

    auto* windowModule = Engine::GetInstance()->GetModule<Window>();
    if (!windowModule) {
        throw std::runtime_error("InputManager window module not found!");
    }

    window = windowModule->GetWindow();

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, CursorPositionCallback);
    glfwSetScrollCallback(window, ScrollCallback);
}

void InputManager::ResetInputsState() {
    previousKeyStates = currentKeyStates;
    previousMouseButtonStates = currentMouseButtonStates;
    mouseMoved = false;
    scrollDelta = 0.0f;
}

void InputManager::Update() {
    for (const auto& pair : currentKeyStates) {
        if (pair.second) {
            std::cout << "InputManager key pressed: " << pair.first << std::endl;
        }
    }

    for (const auto& pair : currentMouseButtonStates) {
        if (pair.second) {
            std::cout << "InputManager mouse button pressed: " << pair.first << std::endl;
        }
    }

    if (mouseMoved) {
        //std::cout << "InputManager mouse position: " << mouseX << ", " << mouseY << std::endl;
    }
}

bool InputManager::GetWhetherAnyInput() {
    bool hasInput = GetAnyKeyDown() || GetAnyMouseButtonDown() || mouseMoved || (scrollDelta != 0.0f);
    if (hasInput) {
        std::cout << "InputManager input detected!" << std::endl;
    }
    return hasInput;
}

#pragma region Keyboard Inputs

bool InputManager::GetAnyKeyDown() {
    for (const auto& pair : currentKeyStates) {
        if (pair.second && !previousKeyStates[pair.first]) {
            std::cout << "InputManager new key pressed: " << pair.first << std::endl;
            return true;
        }
    }
    return false;
}

bool InputManager::GetWhichKeyDown(KeyRepresentation& key) {
    for (const auto& pair : currentKeyStates) {
        if (pair.second && !previousKeyStates[pair.first]) {
            key = static_cast<KeyRepresentation>(pair.first);
            std::cout << "InputManager key down detected: " << pair.first << std::endl;
            return true;
        }
    }
    return false;
}

bool InputManager::GetKeyDown(const KeyRepresentation key) {
    int keyValue = static_cast<int>(key);
    bool isDown = currentKeyStates[keyValue] && !previousKeyStates[keyValue];
    if (isDown) {
        std::cout << "InputManager specific key down: " << keyValue << std::endl;
    }
    return isDown;
}

bool InputManager::GetKey(const KeyRepresentation key) {
    bool isPressed = currentKeyStates[static_cast<int>(key)];
    if (isPressed) {
        std::cout << "InputManager key held: " << static_cast<int>(key) << std::endl;
    }
    return isPressed;
}

bool InputManager::GetKeyUp(const KeyRepresentation key) {
    int keyValue = static_cast<int>(key);
    bool isUp = !currentKeyStates[keyValue] && previousKeyStates[keyValue];
    if (isUp) {
        std::cout << "InputManager key released: " << keyValue << std::endl;
    }
    return isUp;
}

#pragma endregion

#pragma region Mouse Inputs

#pragma region Buttons

bool InputManager::GetAnyMouseButtonDown() {
    for (const auto& pair : currentMouseButtonStates) {
        if (pair.second && !previousMouseButtonStates[pair.first]) {
            std::cout << "InputManager new mouse button pressed: " << pair.first << std::endl;
            return true;
        }
    }
    return false;
}

bool InputManager::GetWhichMouseButtonDown(MouseButtonRepresentation& button) {
    for (const auto& pair : currentMouseButtonStates) {
        if (pair.second && !previousMouseButtonStates[pair.first]) {
            button = static_cast<MouseButtonRepresentation>(pair.first);
            std::cout << "InputManager mouse button down detected: " << pair.first << std::endl;
            return true;
        }
    }
    return false;
}

bool InputManager::GetMouseButtonDown(const MouseButtonRepresentation button) {
    int buttonValue = static_cast<int>(button);
    bool isDown = currentMouseButtonStates[buttonValue] && !previousMouseButtonStates[buttonValue];
    if (isDown) {
        std::cout << "InputManager specific mouse button down: " << buttonValue << std::endl;
    }
    return isDown;
}

bool InputManager::GetMouseButton(const MouseButtonRepresentation button) {
    bool isPressed = currentMouseButtonStates[static_cast<int>(button)];
    if (isPressed) {
        std::cout << "InputManager mouse button held: " << static_cast<int>(button) << std::endl;
    }
    return isPressed;
}

bool InputManager::GetMouseButtonUp(const MouseButtonRepresentation button) {
    int buttonValue = static_cast<int>(button);
    bool isUp = !currentMouseButtonStates[buttonValue] && previousMouseButtonStates[buttonValue];
    if (isUp) {
        std::cout << "InputManager mouse button released: " << buttonValue << std::endl;
    }
    return isUp;
}

#pragma endregion

#pragma region Position

Vector2Representation InputManager::GetMousePosition() {
    std::cout << "InputManager mouse position queried: " << mouseX << ", " << mouseY << std::endl;
    return Vector2Representation(static_cast<float>(mouseX), static_cast<float>(mouseY));
}

bool InputManager::GetWetherAnyMouseMotion() {
    if (mouseMoved) {
        std::cout << "InputManager mouse motion detected" << std::endl;
    }
    return mouseMoved;
}

Vector2Representation InputManager::GetMouseDelta() {
    Vector2Representation delta(
        static_cast<float>(mouseX - lastMouseX),
        static_cast<float>(mouseY - lastMouseY)
    );
    std::cout << "InputManager mouse delta: " << delta.x << ", " << delta.y << std::endl;
    return delta;
}

#pragma endregion

#pragma region Wheel

float InputManager::GetMouseWheelDelta() {
    if (scrollDelta != 0.0f) {
        std::cout << "InputManager mouse wheel delta: " << scrollDelta << std::endl;
    }
    return scrollDelta;
}

#pragma endregion

#pragma endregion

void InputManager::Shutdown() {
    std::cout << "InputManager shutting down" << std::endl;
}

void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (instance) {
        instance->currentKeyStates[key] = (action != GLFW_RELEASE);
    }
}

void InputManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (instance) {
        instance->currentMouseButtonStates[button] = (action != GLFW_RELEASE);
    }
}

void InputManager::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    if (instance) {
        instance->lastMouseX = instance->mouseX;
        instance->lastMouseY = instance->mouseY;
        instance->mouseX = xpos;
        instance->mouseY = ypos;
        instance->mouseMoved = true;
    }
}

void InputManager::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    if (instance) {
        instance->scrollDelta = static_cast<float>(yoffset);
    }
}