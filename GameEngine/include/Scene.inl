#include "GameObject.hpp"

inline void Scene::MarkGameObjectForDeletion(GameObject* gameObjectPtr) {
	gameObjectsMarkedForDeletion.push_back(gameObjectPtr);
}

inline void Scene::DeleteGameObjects() {

	for (GameObject* toDeletePtr : gameObjectsMarkedForDeletion) {
		DeleteGameObject(toDeletePtr);
	}

	gameObjectsMarkedForDeletion.clear();
}

inline void Scene::DeleteGameObject(GameObject* gameObjectPtr) {

	gameObjects.erase(std::find(gameObjects.begin(), gameObjects.end(), gameObjectPtr));

	gameObjectPtr->OnDestroy();

	delete gameObjectPtr;
}