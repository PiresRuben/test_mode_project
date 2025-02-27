#include "Modules/ScenesManager.hpp"
#include "Scene.hpp"

template <typename SceneName> static void ScenesManager::AddScene(bool doStartActive) {
#if DEBUG
	std::string sceneAsStr = typeid(SceneName).name();
	if (instance->scenes.count(sceneAsStr) > 0) {

		std::cerr << "There is already a scene named: " << sceneAsStr << std::endl;
		throw new std::runtime_error("^^");
	}
#endif
	Scene* newScene = static_cast<Scene*>(new SceneName(doStartActive));
	instance->initScenes += [=]() { newScene->Init(); };
	instance->scenes[typeid(SceneName).name()] = newScene;
}

template <typename SceneName> static void ScenesManager::RemoveScene() {

	std::string& sceneAsStr = typeid(SceneName).name();
	delete instance->scenes[sceneAsStr];
	instance->scenes.erase(sceneAsStr);
}

template <typename SceneName> static void ScenesManager::LoadScene(bool additive) {

	if (!additive) {
		UnloadAllScenes();
	}

	instance->scenes[typeid(SceneName).name()]->Active = true;
}

template <typename ...ScenesNames> static void ScenesManager::LoadScenes(bool additive) {

	if (!additive) {
		UnloadAllScenes();
	}

	(LoadScene<ScenesNames>(true), ...);
}

template <typename SceneName> static void ScenesManager::UnloadScene() {

	instance->scenes[typeid(SceneName).name()]->active = false;
}

template <typename ...ScenesNames> static void ScenesManager::UnloadScenes() {

	(UnloadScene<ScenesNames>(), ...);
}

template <typename SceneName> static Scene* ScenesManager::GetScene() {
#if DEBUG
	std::string sceneAsStr = typeid(SceneName).name();
	if (instance->scenes.count(sceneAsStr) == 0) {

		std::cerr << "There is no scene named: " << sceneAsStr << std::endl;
		throw new std::runtime_error("^^");
	}
#endif
	return instance->scenes[typeid(SceneName).name()];
}
