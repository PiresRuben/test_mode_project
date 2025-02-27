#ifndef PHYSICSMODULE_HPP
#define PHYSICSMODULE_HPP

#include "Module.hpp"
#include "Physics/PhysicsSystem.hpp"

class PhysicsModule : public Module {
public:
    PhysicsModule();
    ~PhysicsModule();

    void Init() override;
    void Update() override;
    void Shutdown() override;

private:
    PhysicsSystem* physicsSystem;
};

#endif // PHYSICSMODULE_HPP