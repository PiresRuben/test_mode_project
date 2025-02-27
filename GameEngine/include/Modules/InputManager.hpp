#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>
#include "Module.hpp"
#include "Vector2Representation.hpp"
#include "InputEnums.hpp"

class InputManager : public Module {
private:
    static InputManager* instance;
    GLFWwindow* window = nullptr;

    std::unordered_map<int, bool> currentKeyStates;
    std::unordered_map<int, bool> previousKeyStates;

    std::unordered_map<int, bool> currentMouseButtonStates;
    std::unordered_map<int, bool> previousMouseButtonStates;

    double mouseX = 0.0, mouseY = 0.0;
    double lastMouseX = 0.0, lastMouseY = 0.0;
    float scrollDelta = 0.0f;
    bool mouseMoved = false;

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

public:
    InputManager();
    void SetWindow(GLFWwindow* window);
    void ResetInputsState();
    void Init() override;
    void Update() override;
    void Shutdown() override;

    bool GetWhetherAnyInput();

    bool GetAnyKeyDown();
    bool GetWhichKeyDown(KeyRepresentation& key);
    bool GetKeyDown(const KeyRepresentation key);
    bool GetKey(const KeyRepresentation key);
    bool GetKeyUp(const KeyRepresentation key);

    bool GetAnyMouseButtonDown();
    bool GetWhichMouseButtonDown(MouseButtonRepresentation& button);
    bool GetMouseButtonDown(const MouseButtonRepresentation button);
    bool GetMouseButton(const MouseButtonRepresentation button);
    bool GetMouseButtonUp(const MouseButtonRepresentation button);

    Vector2Representation GetMousePosition();
    bool GetWetherAnyMouseMotion();
    Vector2Representation GetMouseDelta();
    float GetMouseWheelDelta();
};