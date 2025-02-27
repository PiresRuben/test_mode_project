#include "GameObject.hpp"
#include "Component.hpp"
#include "Components/Transform.hpp"


void GameObject::Update() {

	for (std::shared_ptr<Component> component : components) {
		component->Update();
	}

#ifdef DEBUG
	if (trackedAs == "") { return; }
	std::cout << trackedAs << " was updated\n";
#endif
}

void GameObject::Render() {
	return;

	std::shared_ptr<class Renderable> renderablePtr = nullptr;
	for (std::shared_ptr<Component> component : components) {

		//renderablePtr = std::dynamic_pointer_cast<Renderable>(component);
		if (renderablePtr == nullptr) { continue; }
		
		// renderablePtr->Render();
	}

#ifdef DEBUG
	if (trackedAs == "") { return; }
	std::cout << trackedAs << " was rendered\n";
#endif
}

#ifdef DEBUG
void GameObject::OnDebug() {

	for (std::shared_ptr<Component> component : components) {

		component->OnDebug();

		if (false) { // if selected
			component->OnDebugSelected();
		}
	}
}
#endif

void GameObject::OnDestroy() {

	for (std::shared_ptr<Component> component : components) {
		component->OnDestroy();
	}

#ifdef DEBUG
	if (trackedAs == "") { return; }
	std::cout << trackedAs << " was destroyed\n";
#endif
}

void GameObject::SetTransform(std::shared_ptr<Transform> transform_) {
	transform = transform_;
}