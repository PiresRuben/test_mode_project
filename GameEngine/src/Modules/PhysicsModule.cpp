#include "Modules/PhysicsModule.hpp"
#include <iostream>

PhysicsModule::PhysicsModule() : physicsSystem(nullptr) {}

PhysicsModule::~PhysicsModule() {
    Shutdown();
}

void PhysicsModule::Init() {
    std::cout << "PhysicsModule: Starting initialization" << std::endl;

    try {
        physicsSystem = new PhysicsSystem();
        if (!physicsSystem->Init()) {
            std::cerr << "PhysicsModule: Failed to initialize physics system" << std::endl;
            Shutdown();
            return;
        }
        std::cout << "PhysicsModule: Initialization complete" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "PhysicsModule: Initialization failed with error: " << e.what() << std::endl;
        Shutdown();
    }
}

void PhysicsModule::Update() {
    if (!physicsSystem) return;

    try {
        float deltaTime = 1.0f / 60.0f;
        physicsSystem->Update(deltaTime);
    }
    catch (const std::exception& e) {
        std::cerr << "PhysicsModule: Update failed: " << e.what() << std::endl;
    }
}

void PhysicsModule::Shutdown() {
    if (physicsSystem) {
        physicsSystem->Shutdown();
        delete physicsSystem;
        physicsSystem = nullptr;
    }
}