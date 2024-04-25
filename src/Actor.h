 #pragma once

#include <string>
#include <vector>
#include "Components/Component.h"

class Component;

class Actor
{
public:
	Actor(std::string name)
		: mName(name) {}

	void Start();
	void Update();
	void LateUpdate();
	void Destroy();

	std::string& GetName() { return mName; }
	bool IsInitialized() { return mInitialized; }

	template<class T>
	T* AddComponent()
	{
		T* newComponent = new T;
		newComponent->mParent = this;
		mComponents.push_back(newComponent);
		return newComponent;
	}

	template<class T>
	T* GetComponent()
	{
		for (Component* component : mComponents)
		{
			T* castedComponent = dynamic_cast<T*>(component);
			if (castedComponent)
				return castedComponent;
		}
		return nullptr;
	}

	template<class T>
	T* GetOrAddComponent()
	{
		T* component = GetComponent<T>();
		if (component)
			return component;
		return AddComponent<T>();
	}

	std::vector<Component*>& GetComponents() { return mComponents; }

private:
	bool mInitialized = false;
	std::string mName = "";
	std::vector<Component*> mComponents;

};

