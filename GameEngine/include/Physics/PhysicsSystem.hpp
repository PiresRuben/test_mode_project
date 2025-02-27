#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include <Jolt/Jolt.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/JobSystem.h>
#include <Jolt/Core/JobSystemWithBarrier.h>
#include <Core/Maths/glm.hpp>

// Forward declarations
namespace JPH {
    class TempAllocatorImpl;
    class BroadPhaseLayerInterface;
    class ObjectVsBroadPhaseLayerFilter;
    class ObjectLayerPairFilter;
}

class PhysicsSystem {
public:
    PhysicsSystem();
    ~PhysicsSystem();

    bool Init();
    void Update(float deltaTime);
    void Shutdown();
    void SetGravity(const glm::vec3& gravity);

private:
    bool InitializeJoltTypes();
    bool CreatePhysicsSystem();

    JPH::PhysicsSystem* mPhysicsSystem;
    JPH::TempAllocatorImpl* mTempAllocator;
    JPH::BroadPhaseLayerInterface* mBroadPhaseLayerInterface;
    JPH::ObjectVsBroadPhaseLayerFilter* mObjectVsBroadPhaseLayerFilter;
    JPH::ObjectLayerPairFilter* mObjectLayerPairFilter;
    bool mIsInitialized;
};

#endif