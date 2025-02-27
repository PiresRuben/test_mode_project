#pragma once

#include <vector>

#include "Module.hpp"


class Engine {
    
public:
    Engine();
    ~Engine();

    void Run();
    static Engine* GetInstance();

    template <typename ModuleType> ModuleType* GetModule() const {

        ModuleType* correctModule = nullptr;
        for (Module* module : modules) {

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
	void Init();
	void Update();
	void Render();
	void Shutdown();

    bool ShouldRun() const;

	std::vector<Module*> modules;
	void CreateModules();
	template<typename ModuleType> void CreateModule() {
		modules.push_back(new ModuleType());
	}

};