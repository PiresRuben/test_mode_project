#include "Engine.hpp"

#include "Modules/InputManager.hpp"
#include "Modules/ScenesManager.hpp"
#include "Modules/Time.hpp"
#include "Modules/AudioManager.hpp"
#include "Modules/Window.hpp"
#include "Modules/RenderModule.hpp"
#include "Modules/PhysicsModule.hpp"

#include "Utilities/ImGUI.hpp"

Engine* Engine::instance = nullptr;
#ifdef DEBUG
bool Engine::debugModeEnabled = false;
#endif


Engine::Engine() {
    if (instance != nullptr) { throw std::runtime_error("Engine instance already exists!"); }

    instance = this;
}

Engine::~Engine() {}

Engine* Engine::GetInstance() {
    return instance;
}

void Engine::Run() {
    Init();

	while (ShouldRun()) {
		Update();

		ImGUI::Begin("Hi ^^");
		ImGUI::Text("^^");
		ImGUI::End();

		Render();
	}

    Shutdown();
}

bool Engine::ShouldRun() const {
    auto* window = GetModule<Window>();
    return window != nullptr ? !window->ShouldClose() : false;
}

void Engine::CreateModules() {
	// Graphics related modules first
	CreateModule<Window>();
	CreateModule<RenderModule>();

	// Core modules
	CreateModule<InputManager>();
	CreateModule<Time>();
	CreateModule<ScenesManager>();
	CreateModule<AudioManager>();

	// Physics last
	try {
		CreateModule<PhysicsModule>();
	}
	catch (const std::exception& e) {
		std::cerr << "Failed to create Physics Module: " << e.what() << std::endl;
		// Handle error or continue without physics
	}
}

void Engine::Init() {
	std::cout << "Init Starting\n";

	CreateModules();
	std::cout << "CreateModules done\n";

	for (Module* module : modules) {
		module->Init();
	}

	std::cout << "Init Done\n";
}

void Engine::Update() {

	for (Module* module : modules) {
		module->Update();
	}
}

void Engine::Render() {
	
	for (Module* module : modules) {
		module->Render();
	}
}

void Engine::Shutdown() {
	
	for (Module* module : modules) {
		module->Shutdown();
		delete module;
	}
}


