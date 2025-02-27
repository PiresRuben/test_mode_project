#pragma once

#include <iostream>
#include <unordered_map>

#include "Utilities/MulticastDelegate.hpp"
#include "Module.hpp"
#include "Scene.hpp"


class ScenesManager : public Module {
	
public:
	ScenesManager();

	void Update() override;
	void Render() override;
	void Shutdown() override;

	template <typename SceneName> static void AddScene(bool doStartActive = false);
	template <typename SceneName> static void RemoveScene();
	template <typename SceneName> static void LoadScene(bool additive = false);
	template <typename ...ScenesNames> static void LoadScenes(bool additive = false);
	template <typename SceneName> static void UnloadScene();
	template <typename ...ScenesNames> static void UnloadScenes();

	void UnloadAllScenes();

	template <typename SceneName> static Scene* GetScene();

	static Scene* persistentScene;
private:

	static ScenesManager* instance;
	std::unordered_map<std::string, Scene*> scenes;
	MulticastDelegate<> initScenes = MulticastDelegate(true);
};

#include "Modules/ScenesManager.inl"