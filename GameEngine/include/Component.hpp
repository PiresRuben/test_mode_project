#pragma once

#include <memory>

class Component {
	
public:
	class GameObject* Owner = nullptr;
	bool enabled = false;
	virtual void Enable();
	virtual void Disable();
	void SetOwner(GameObject* entity);
	std::shared_ptr<class Transform> Transform() const;

	virtual inline void Awake() { }
	virtual inline void Update() { }
#ifdef DEBUG
	virtual inline void OnDebug() { }
	virtual inline void OnDebugSelected() { }
#endif
	virtual inline void OnDestroy() { }

	template<typename TComponent> std::shared_ptr<TComponent> AddComponent();
	template<typename TComponent> bool TryGetComponent(std::shared_ptr<TComponent>& returnPtr, const int skipOccurences = 0);
	template<typename TComponent> bool TryGetComponents(std::vector<std::shared_ptr<TComponent>>& returnPtrArray);
	template<typename TComponent> std::shared_ptr<TComponent> GetComponent(const int skipOccurences = 0);
	template<typename TComponent> std::vector<std::shared_ptr<TComponent>> GetComponents();
	template<typename TComponent> void RemoveComponent(const int skipOccurences = 0);
	template<typename TComponent> bool TryRemoveComponent(const int skipOccurences = 0);

};

#include "Component.inl"
