#include "Modules/ScenesManager.hpp"
#include "Modules/RenderModule.hpp"
#include "Scene.hpp"
#include "Utilities/ImGUI.hpp"

#include "DefaultScene.hpp"

ScenesManager* ScenesManager::instance = nullptr;
Scene* ScenesManager::persistentScene = nullptr;

ScenesManager::ScenesManager() {

	if (instance != nullptr) { throw std::runtime_error("FFS"); }

	instance = this;
	persistentScene = new Scene(true);

	AddScene<DefaultScene>(true); // NO :D
}

void ScenesManager::Update() {

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	initScenes();

	persistentScene->Update();

	for (auto& [__, scene] : scenes) {

		if (!scene->active) { continue; }

		scene->Update();
	}
}

void ScenesManager::Render() {
	if (Engine::GetModule<RenderModule>()->mainCamera == nullptr) { return; }

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
