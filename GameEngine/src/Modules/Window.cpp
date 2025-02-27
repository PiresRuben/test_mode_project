#include "Modules/Window.hpp"
#include <iostream>
#include <stdexcept>

//Window::Data Window::WindowData;

Window::Window(int width, int height, const char* title) : width(width), height(height), title(title), window(nullptr), shouldClose(false){
    std::cout << "Window created" << std::endl;
    // WindowData.SetSize(width, height);
	// ImGui::whatever::Init(<*window>);	
}

Window::~Window() {
    Shutdown();
}

void Window::Init() {
    std::cout << "Window initializing" << std::endl;

    if (!glfwInit()) {
        throw std::runtime_error("Window failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Stop GLFW from Creating an OpenGL Context
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
		glfwTerminate(); //cleanup
        throw std::runtime_error("Window failed to create window");
    }

    SetVSync(true); //Vsync because why not

    std::cout << "Window initialized successfully" << std::endl;
}

void Window::Update() {
    shouldClose = glfwWindowShouldClose(window);
    glfwPollEvents();
}

void Window::Shutdown() {
    std::cout << "Window shutting down" << std::endl;
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}

glm::ivec2 Window::GetSize() const {
    int w, h;
    glfwGetWindowSize(window, &w, &h);
    return glm::ivec2(w, h);
}

void Window::SetVSync(bool enabled) {
    glfwSwapInterval(enabled ? 1 : 0);
}

void Window::SetTitle(const char* newTitle) {
    title = newTitle;
    if (window) {
        glfwSetWindowTitle(window, title);
    }
}

void Window::ToggleFullscreen() {
    if (window == nullptr) { return; }

    static int windowed_x = 0, windowed_y = 0;
    static int windowed_width = width, windowed_height = height;

    if (glfwGetWindowMonitor(window)) {
        glfwSetWindowMonitor(window, nullptr, windowed_x, windowed_y, windowed_width, windowed_height, GLFW_DONT_CARE);
    }
    else {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        if (!monitor) return;

        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        if (!mode) return;

        glfwGetWindowPos(window, &windowed_x, &windowed_y);
        glfwGetWindowSize(window, &windowed_width, &windowed_height);

        glfwSetWindowMonitor(window, monitor,0, 0, mode->width, mode->height, mode->refreshRate);
    }
}