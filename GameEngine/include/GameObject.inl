#include <iostream>
#include <algorithm>

#include "assert.h"

#include "Scene.hpp"
#include "Component.hpp"


inline GameObject::GameObject(Scene* parentScene_, bool enabled_) {

	enabled = enabled_;
	parentScene = parentScene_;
}

inline void GameObject::Disable() {

	for (std::shared_ptr<Component> component : components) {
		component->Disable();
	}

	enabled = false;

#ifdef DEBUG
	if (trackedAs == "") { return; }
	std::cout << trackedAs << " was disabled\n";
#endif
}

inline void GameObject::Enable() {

	for (std::shared_ptr<Component> component : components) {
		component->Enable();
	}

	enabled = true;

#ifdef DEBUG
	if (trackedAs == "") { return; }
	std::cout << trackedAs << " was enabled\n";
#endif
}

// Only throws when TComponent does not inherit component (or the GameObject s parent scene is nullptr)
template<typename TComponent> std::shared_ptr<TComponent> GameObject::AddComponent() {

	std::shared_ptr<TComponent> componentPtr = std::make_shared<TComponent>();
	std::shared_ptr<Component> asComponent = std::static_pointer_cast<Component>(componentPtr);

	asComponent->SetOwner(this);

	components.push_back(asComponent);

	parentScene->QueueAwake([=]() { asComponent->Awake(); });

	return componentPtr;
}

template<typename TComponent> bool GameObject::TryGetComponent(std::shared_ptr<TComponent>& returnPtr, int skipOccurences) {

	returnPtr = nullptr;
	std::shared_ptr<Component> relevantComponent = nullptr;
	for (std::shared_ptr<Component> component : components) {

		relevantComponent = std::dynamic_pointer_cast<Component>(component);
		if (relevantComponent == nullptr) { continue; }

		if (skipOccurences-- > 0) { continue; }

		returnPtr = std::static_pointer_cast<TComponent>(relevantComponent);
		return true;
	}

	return false;
}

template<typename TComponent> bool GameObject::TryGetComponents(std::vector<std::shared_ptr<TComponent>>& returnPtrArray) {

	bool gotAtLeastOne = false;
	std::shared_ptr<Component> relevantComponent = nullptr;
	for (std::shared_ptr<Component> component : components) {

		relevantComponent = std::dynamic_pointer_cast<Component>(component);
		if (relevantComponent == nullptr) { continue; }

		returnPtrArray.push_back(std::static_pointer_cast<TComponent>(relevantComponent));

		gotAtLeastOne = true;
	}

	return gotAtLeastOne;
}

template<typename TComponent> std::shared_ptr<TComponent> GameObject::GetComponent(int skipOccurences) {

	std::shared_ptr<Component> relevantComponent = nullptr;
	for (std::shared_ptr<Component> component : components) {

		relevantComponent = std::dynamic_pointer_cast<Component>(component);
		if (relevantComponent == nullptr) { continue; }

		if (skipOccurences-- > 0) { continue; }

		return std::static_pointer_cast<TComponent>(relevantComponent);
	}

	return nullptr;
}

template<typename TComponent> std::vector<std::shared_ptr<TComponent>> GameObject::GetComponents() {
	
	std::vector<std::shared_ptr<TComponent>> toReturn;

	std::shared_ptr<Component> relevantComponent = nullptr;
	for (std::shared_ptr<Component> component : components) {

		relevantComponent = std::dynamic_pointer_cast<Component>(component);
		if (relevantComponent == nullptr) { continue; }

		toReturn.push_back(std::static_pointer_cast<TComponent>(relevantComponent));
	}
	
	return toReturn;
}

template<typename TComponent> void GameObject::RemoveComponent(int skipOccurences) {

	std::shared_ptr<Component> relevantComponent = nullptr;
	for (std::shared_ptr<Component> component : components) {

		relevantComponent = std::dynamic_pointer_cast<Component>(component);
		if (relevantComponent == nullptr) { continue; }

		if (skipOccurences-- > 0) { continue; }

		components.erase(std::find(components.begin(), components.end(), component));

		return;
	}
}

template<typename TComponent> bool GameObject::TryRemoveComponent(int skipOccurences) {

	std::shared_ptr<Component> relevantComponent = nullptr;
	for (std::shared_ptr<Component> component : components) {

		relevantComponent = std::dynamic_pointer_cast<Component>(component);
		if (relevantComponent == nullptr) { continue; }

		if (skipOccurences-- > 0) { continue; }

		components.erase(std::find(components.begin(), components.end(), component));

		return true;
	}

	return false;
}

