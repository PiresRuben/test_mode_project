#include "Modules/ScenesManager.hpp"
#include "Scene.hpp"

//#include "DefaultScene.hpp"

ScenesManager* ScenesManager::instance = nullptr;
Scene* ScenesManager::persistentScene = nullptr;

ScenesManager::ScenesManager() {

	if (instance != nullptr) { throw std::runtime_error("FFS"); }

	instance = this;
	persistentScene = new Scene(true);

	//AddScene<DefaultScene>(true); // NO :D
}

void ScenesManager::Update() {

	initScenes();

	persistentScene->Update();

	for (auto& [__, scene] : scenes) {

		if (!scene->active) { continue; }

		scene->Update();
	}
}

void ScenesManager::Render() {

	persistentScene->Render();

	for (auto& [__, scene] : scenes) {

		if (!scene->active) { continue; }

		scene->Render();
	}
}


void ScenesManager::Shutdown() {

	persistentScene->OnDestroy();
	delete persistentScene;
	persistentScene = nullptr;

	for (auto& [__, scene] : scenes) {
		scene->OnDestroy();
		delete scene;
		scene = nullptr;
	}
	
	scenes.clear();
}

void ScenesManager::UnloadAllScenes() {

	for (auto& [__, scene] : scenes) {
		scene->active = false;
	}
}
