#include "Scene.hpp"
#include "GameObject.hpp"
#include "Components/Transform.hpp"
#include "Engine.hpp"


Scene::Scene(const bool active_) {
	active = active_;
}

void Scene::Awake() {
	onAwake();
}

void Scene::Update() {

	Awake();

	for (GameObject* gameObject : gameObjects) {

		if (!gameObject->enabled) { continue; }

		gameObject->Update();
	}

	DeleteGameObjects();
}

void Scene::Render() {

	for (GameObject* gameObject : gameObjects) {

		if (!gameObject->enabled) { continue; }

		gameObject->Render();
#ifdef DEBUG
		if (Engine::debugModeEnabled) {

			gameObject->OnDebug();
		}
#endif
	}
}

void Scene::OnDestroy() {

	for (GameObject* gameObject : gameObjects) {

		delete gameObject;
		gameObject = nullptr;
	}

	gameObjects.clear();
}

#ifdef DEBUG
GameObject* Scene::AddGameObject(const std::string& trackLifeCycleAs, const bool startActive) {

	GameObject* newGameObjectPtr = new GameObject(this, startActive);

	newGameObjectPtr->SetTransform(newGameObjectPtr->AddComponent<Transform>());

	gameObjects.push_back(newGameObjectPtr);

	if (trackLifeCycleAs != "") {
		newGameObjectPtr->trackedAs = trackLifeCycleAs;
		std::cout << "Created " << trackLifeCycleAs << "\n";
	}

	return newGameObjectPtr;
}
#else
GameObject* Scene::AddGameObject(const bool startActive) {

	GameObject* newGameObjectPtr = new GameObject(this, startActive);

	newGameObjectPtr->SetTransform(newGameObjectPtr->AddComponent<Transform>());

	gameObjects.push_back(newGameObjectPtr);

	return newGameObjectPtr;
}
#endif

void Scene::QueueAwake(std::function<void(void)> componentAwakeMethod) {
	onAwake += componentAwakeMethod;
}
