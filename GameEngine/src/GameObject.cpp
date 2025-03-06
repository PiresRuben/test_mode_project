#include "GameObject.hpp"
#include "Component.hpp"
#include "Components/Transform.hpp"
#include "Components/Renderable.hpp"


void GameObject::Update() {

	for (GameObject* child : children) {
		child->Update();
	}

	for (std::shared_ptr<Component> component : components) {
		component->Update();
	}

#ifdef DEBUG
	if (trackedAs == "") { return; }
	std::cout << trackedAs << " was updated\n";
#endif
}

void GameObject::Render() {
	
	std::shared_ptr<Renderable> renderablePtr = nullptr;
	for (std::shared_ptr<Component> component : components) {

		renderablePtr = std::dynamic_pointer_cast<Renderable>(component);
		if (renderablePtr == nullptr) { continue; }
		
		 renderablePtr->Render();
	}

#ifdef DEBUG
	if (trackedAs == "") { return; }
	std::cout << trackedAs << " was rendered\n";
#endif
}

#ifdef DEBUG
void GameObject::OnDebug() {

	for (GameObject* child : children) {
		child->OnDebug();
	}

	for (std::shared_ptr<Component> component : components) {

		component->OnDebug();

		if (false) { // if selected
			component->OnDebugSelected();
		}
	}
}
#endif

void GameObject::OnDestroy() {

	for (GameObject* child : children) {
		child->OnDestroy();
	}

	for (std::shared_ptr<Component> component : components) {
		component->OnDestroy();
	}

#ifdef DEBUG
	if (trackedAs == "") { return; }
	std::cout << trackedAs << " was destroyed\n";
#endif
}

#ifdef DEBUG
GameObject* GameObject::AddChild(const std::string& trackLifeCycleAs, const bool startActive) {

	GameObject* newGameObjectPtr = new GameObject(parentScene, startActive);

	newGameObjectPtr->SetTransform(newGameObjectPtr->AddComponent<Transform>());
	newGameObjectPtr->parent = this;

	children.push_back(newGameObjectPtr);

	if (trackLifeCycleAs != "") {
		newGameObjectPtr->trackedAs = trackLifeCycleAs;
		std::cout << "Created " << trackLifeCycleAs << "\n";
	}

	return newGameObjectPtr;
}
#else
GameObject* GameObject::AddChild(const bool startActive) {

	GameObject* newGameObjectPtr = new GameObject(parentScene, startActive);

	newGameObjectPtr->SetTransform(newGameObjectPtr->AddComponent<Transform>());
	newGameObjectPtr->parent = this;

	children.push_back(newGameObjectPtr);

	return newGameObjectPtr;
}
#endif
void GameObject::SetTransform(std::shared_ptr<Transform> transform_) {
	transform = transform_;
}