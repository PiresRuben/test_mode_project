#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>

class GameObject {
	
public:
	GameObject(class Scene* parentScene_, bool enabled_ = true);

	bool enabled = true;
	Scene* parentScene = nullptr;
#ifdef DEBUG
	std::string trackedAs = "";
#endif
	std::shared_ptr<class Transform> transform = nullptr;
	void SetTransform(std::shared_ptr<class Transform> transform_);

	template<typename TComponent> std::shared_ptr<TComponent> AddComponent();
	template<typename TComponent> bool TryGetComponent(std::shared_ptr<TComponent>& returnPtr, int skipOccurences = 0);
	template<typename TComponent> bool TryGetComponents(std::vector<std::shared_ptr<TComponent>>& returnPtrArray);
	template<typename TComponent> std::shared_ptr<TComponent> GetComponent(int skipOccurences = 0);
	template<typename TComponent> std::vector<std::shared_ptr<TComponent>> GetComponents();
	template<typename TComponent> void RemoveComponent(int skipOccurences = 0);
	template<typename TComponent> bool TryRemoveComponent(int skipOccurences = 0);

	void Disable();
	void Enable();

	void Update();
	void Render();
#ifdef DEBUG
	void OnDebug();
#endif
	void OnDestroy();


private:
	std::vector<std::shared_ptr<class Component>> components;
};

#include "GameObject.inl"