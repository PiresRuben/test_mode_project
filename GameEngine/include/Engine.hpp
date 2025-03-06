#pragma once

#include <vector>

#include "Module.hpp"


class Engine {
    
public:
    Engine();
    ~Engine();

    void Run();
    static Engine* GetInstance();

    template <typename ModuleType> static ModuleType* GetModule() {

        ModuleType* correctModule = nullptr;
        for (Module* module : instance->modules) {

            if ((correctModule = dynamic_cast<ModuleType*>(module)) != nullptr) {
                return correctModule;
            }
        }

        return correctModule;
    }

#ifdef DEBUG
	static bool debugModeEnabled;
#endif

private:
    static Engine* instance;
    class Window* window = nullptr;
	void Init();
	void Update();
	void Render();
	void Shutdown();

    bool ShouldRun() const;

	std::vector<Module*> modules;
	void CreateModules();
	template<typename ModuleType> ModuleType* CreateModule() {
        ModuleType* module = new ModuleType();
		modules.push_back(module);
        return module;
	}

};