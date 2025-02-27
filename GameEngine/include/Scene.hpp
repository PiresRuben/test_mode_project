#pragma once

#include <string>

#include "Module.hpp"
#include "Utilities/MulticastDelegate.hpp"

#ifdef DEBUG
	#define AddGameObjectTracked(startActive, trackAs) AddGameObject(trackAs, startActive)
	#define AddGameObjectUntracked(startActive) AddGameObject("", startActive)
#else
	#define AddGameObjectTracked(startActive, trackAs) AddGameObject(startActive)
	#define AddGameObjectUntracked(startActive) AddGameObject(startActive)
#endif


class Scene {

public:
	Scene(bool active);
	bool active = true;

	virtual void Init() { }

	void Awake();
	void Update();
	void Render();
	void OnDestroy();

#ifdef DEBUG
	class GameObject* AddGameObject(const std::string& trackLifeCycleAs, const bool startActive = true);
#else
	class GameObject* AddGameObject(const bool startActive = true);
#endif
	void QueueAwake(std::function<void(void)> componentAwakeMethod);
	void MarkGameObjectForDeletion(GameObject* gameObjectPtr);

protected:
	std::vector<GameObject*> gameObjects;
	std::vector<GameObject*> gameObjectsMarkedForDeletion;

private:
	MulticastDelegate<> onAwake = MulticastDelegate<>(true);

	void DeleteGameObjects();
	void DeleteGameObject(GameObject* gameObjectPtr);
};

#include "Scene.inl"