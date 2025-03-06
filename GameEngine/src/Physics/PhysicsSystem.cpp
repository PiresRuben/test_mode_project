#include "Physics/PhysicsSystem.hpp"
#include <Jolt/Core/TempAllocator.h>
#include <iostream>

namespace {
    class BPLayerInterfaceImpl : public JPH::BroadPhaseLayerInterface {
    public:
        virtual JPH::uint GetNumBroadPhaseLayers() const override { return 1; }
        virtual JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override {
            return JPH::BroadPhaseLayer(0);
        }
#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
        virtual const char* GetBroadPhaseLayerName(JPH::BroadPhaseLayer inLayer) const override {
            return "Default";
        }
#endif
    };

    class ObjectVsBroadPhaseLayerFilterImpl : public JPH::ObjectVsBroadPhaseLayerFilter {
    public:
        virtual bool ShouldCollide(JPH::ObjectLayer inLayer1, JPH::BroadPhaseLayer inLayer2) const override {
            return true;
        }
    };

    class ObjectLayerPairFilterImpl : public JPH::ObjectLayerPairFilter {
    public:
        virtual bool ShouldCollide(JPH::ObjectLayer inObject1, JPH::ObjectLayer inObject2) const override {
            return true;
        }
    };
}

PhysicsSystem::PhysicsSystem()
    : mPhysicsSystem(nullptr)
    , mTempAllocator(nullptr)
    , mBroadPhaseLayerInterface(nullptr)
    , mObjectVsBroadPhaseLayerFilter(nullptr)
    , mObjectLayerPairFilter(nullptr)
    , mIsInitialized(false) {
}

PhysicsSystem::~PhysicsSystem() {
    Shutdown();
}

bool PhysicsSystem::InitializeJoltTypes() {
    try {
        std::cout << "Physics System: Initializing Jolt types" << std::endl;

        // Enregistrement de l'allocateur par défaut
        JPH::RegisterDefaultAllocator();
        std::cout << "Physics System: Default allocator registered" << std::endl;

        // Création de la factory
        if (!JPH::Factory::sInstance) {
            JPH::Factory::sInstance = new JPH::Factory();
            if (!JPH::Factory::sInstance) {
                throw std::runtime_error("Failed to create JPH::Factory instance");
            }
        }
        std::cout << "Physics System: Factory created" << std::endl;

        // Important: Enregistrer les types avant de créer le système physique
        JPH::RegisterTypes();
        std::cout << "Physics System: Types registered" << std::endl;

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Physics System: Failed to initialize Jolt types: " << e.what() << std::endl;
        return false;
    }
}

bool PhysicsSystem::CreatePhysicsSystem() {
    try {
        std::cout << "Physics System: Creating physics system" << std::endl;

        // Création des composants avec vérification
        try {
            mTempAllocator = new JPH::TempAllocatorImpl(32 * 1024);
            if (!mTempAllocator) {
                throw std::runtime_error("Failed to allocate TempAllocator");
            }
            std::cout << "Physics System: Temp allocator created" << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Failed to create temp allocator: " << e.what() << std::endl;
            return false;
        }

        try {
            mBroadPhaseLayerInterface = new BPLayerInterfaceImpl();
            mObjectVsBroadPhaseLayerFilter = new ObjectVsBroadPhaseLayerFilterImpl();
            mObjectLayerPairFilter = new ObjectLayerPairFilterImpl();
            if (!mBroadPhaseLayerInterface || !mObjectVsBroadPhaseLayerFilter || !mObjectLayerPairFilter) {
                throw std::runtime_error("Failed to allocate interface components");
            }
            std::cout << "Physics System: Interfaces created" << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Failed to create interfaces: " << e.what() << std::endl;
            return false;
        }

        // Création du système physique avec vérification
        try {
            mPhysicsSystem = new JPH::PhysicsSystem();
            if (!mPhysicsSystem) {
                throw std::runtime_error("Failed to allocate PhysicsSystem");
            }
            std::cout << "Physics System: System instance created" << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Failed to create physics system: " << e.what() << std::endl;
            return false;
        }

        // Initialisation avec des paramètres minimaux
        try {
            const JPH::uint maxBodies = 10;
            const JPH::uint numBodyMutexes = 0;
            const JPH::uint maxBodyPairs = 10;
            const JPH::uint maxContactConstraints = 10;

            mPhysicsSystem->Init(
                maxBodies,
                numBodyMutexes,
                maxBodyPairs,
                maxContactConstraints,
                *mBroadPhaseLayerInterface,
                *mObjectVsBroadPhaseLayerFilter,
                *mObjectLayerPairFilter
            );
            std::cout << "Physics System: System initialized" << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Failed to initialize physics system: " << e.what() << std::endl;
            return false;
        }

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Physics System: Failed to create physics system: " << e.what() << std::endl;
        return false;
    }
}

bool PhysicsSystem::Init() {
    std::cout << "Physics System: Starting initialization" << std::endl;

    if (!InitializeJoltTypes()) {
        std::cerr << "Physics System: Failed to initialize Jolt types" << std::endl;
        return false;
    }

    if (!CreatePhysicsSystem()) {
        std::cerr << "Physics System: Failed to create physics system" << std::endl;
        return false;
    }

    mIsInitialized = true;
    std::cout << "Physics System: Initialization complete" << std::endl;
    return true;
}

void PhysicsSystem::Update(float deltaTime) {
    if (mIsInitialized && mPhysicsSystem) {
        try {
            mPhysicsSystem->Update(deltaTime, 1, mTempAllocator, nullptr);
        }
        catch (const std::exception& e) {
            std::cerr << "Physics System: Update error: " << e.what() << std::endl;
        }
    }
}

void PhysicsSystem::Shutdown() {
    std::cout << "Physics System: Starting shutdown" << std::endl;

    delete mPhysicsSystem;
    mPhysicsSystem = nullptr;

    delete mTempAllocator;
    mTempAllocator = nullptr;

    delete mBroadPhaseLayerInterface;
    mBroadPhaseLayerInterface = nullptr;

    delete mObjectVsBroadPhaseLayerFilter;
    mObjectVsBroadPhaseLayerFilter = nullptr;

    delete mObjectLayerPairFilter;
    mObjectLayerPairFilter = nullptr;

    if (JPH::Factory::sInstance) {
        delete JPH::Factory::sInstance;
        JPH::Factory::sInstance = nullptr;
    }

    mIsInitialized = false;
    std::cout << "Physics System: Shutdown complete" << std::endl;
}

void PhysicsSystem::SetGravity(const glm::vec3& gravity) {
    if (mIsInitialized && mPhysicsSystem) {
        mPhysicsSystem->SetGravity(JPH::Vec3(gravity.x, gravity.y, gravity.z));
    }
}