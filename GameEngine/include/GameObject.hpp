#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>

#ifdef DEBUG
	#define AddChildTracked(startActive, trackAs) AddChild(trackAs, startActive)
	#define AddChildUntracked(startActive) AddChild("", startActive)
#else
	#define AddChildTracked(startActive, trackAs) AddChild(startActive)
	#define AddChildUntracked(startActive) AddChild(startActive)
#endif

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

	template<typename TComponent, typename... Args> std::shared_ptr<TComponent> AddComponent(Args&&... args);
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

#ifdef DEBUG
	GameObject* AddChild(const std::string& trackLifeCycleAs, const bool startActive = true);
#else
	GameObject* AddChild(const bool startActive = true);
#endif

	std::vector<GameObject*> children;
	GameObject* parent = nullptr;
private:
	std::vector<std::shared_ptr<class Component>> components;
};

#include "GameObject.inl"