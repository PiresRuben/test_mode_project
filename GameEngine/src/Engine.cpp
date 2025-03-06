#include "Engine.hpp"

#include "Modules/InputManager.hpp"
#include "Modules/ScenesManager.hpp"
#include "Modules/Time.hpp"
#include "Modules/AudioManager.hpp"
#include "Modules/Window.hpp"
#include "Modules/RenderModule.hpp"
#include "Modules/PhysicsModule.hpp"

#include "Utilities/ImGUI.hpp"
#include "Utilities/Logger.hpp"

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
        Render();
    }

    Shutdown();
}

bool Engine::ShouldRun() const {
    return !window->ShouldClose();
}

void Engine::CreateModules() {
    window = CreateModule<Window>();
    _ = CreateModule<InputManager>();
    _ = CreateModule<Time>();
    _ = CreateModule<ScenesManager>();
    _ = CreateModule<RenderModule>();
    _ = CreateModule<AudioManager>();
    //_ = CreateModule<PhysicsModule>();
}

void Engine::Init() {
    Logger::Init();
    LOG_DEBUG("Init Starting");

    CreateModules();
    LOG_DEBUG("CreateModules done");

    for (Module* module : modules) {
        module->Init();
    }

    LOG_DEBUG("Init Done");
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