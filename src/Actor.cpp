#include "Actor.h"

Actor::Actor(std::string name)
	: mName(name), Ref(nullptr)
{
	Ref = luabridge::newTable(LuaManager::GetLuaState());
	Ref = this;
	mEnabled = true;
}

void Actor::Start()
{
	for (Component* component : mComponents)
		if (component->Enabled)
			component->Start();

	mInitialized = true;
}

void Actor::Update()
{
	if (!mEnabled) return;

	for (Component* component : mComponents)
	{
		if (!component->Enabled)
			continue;

		if (component->Initialized)
			component->Update();
		else
			component->Start();
	}
}

void Actor::LateUpdate()
{
	if (!mEnabled) return;

	for (Component* component : mComponents)
	{
		if (component->Enabled && component->Initialized)
			component->LateUpdate();
	}
}

void Actor::Render()
{
	if (!mEnabled) return;

	for (Component* component : mComponents)
	{
		if (component->Enabled)
			component->Render();
	}
}

void Actor::Destroy()
{
	mEnabled = false;

	for (Component* component : mComponents)
		component->Destroy();
}

void Actor::UpdateRenderComponents()
{
	for (Component* component : mComponents)
	{
		if (!component->Enabled)
			continue;

		if (component->Initialized)
		{
			component->Update();
			component->LateUpdate();
		}
		else
			component->Start();
	}
}

void Actor::AddComponent(Component* component)
{
	luabridge::LuaRef parent = LuaManager::GetComponent(component->Type)->Ref;
	LuaManager::EstablishInheritance(component->Ref, parent);
	component->Ref["actor"] = this;
	component->Ref["key"] = component->Key;
	mComponents.push_back(component);
}

luabridge::LuaRef Actor::LuaGetComponent(std::string type)
{
	std::vector<Component*> componentsOfType;

	for (Component* component : mComponents)
	{
		if (component->Type == type && component->Enabled)
			componentsOfType.push_back(component);
	}

	std::sort(componentsOfType.begin(), componentsOfType.end(),
		[](const Component* a, const Component* b) {
			return a->Key <= b->Key;
		});

	if (componentsOfType.size() && componentsOfType[0]->Enabled) return componentsOfType[0]->Ref;
	else return luabridge::LuaRef(LuaManager::GetLuaState());
}

luabridge::LuaRef Actor::LuaGetComponents(std::string type)
{
	std::vector<Component*> componentsOfType;

	for (Component* component : mComponents)
	{
		if (component->Type == type && component->Enabled)
			componentsOfType.push_back(component);
	}

	std::sort(componentsOfType.begin(), componentsOfType.end(),
		[](const Component* a, const Component* b) {
			return a->Key <= b->Key;
		});

	luabridge::LuaRef table = luabridge::newTable(LuaManager::GetLuaState());
	for (size_t i = 0; i < componentsOfType.size(); ++i)
		table[i + 1] = componentsOfType[i]->Ref;

	return table;
}

luabridge::LuaRef Actor::LuaAddComponent(std::string componentType)
{
	std::string key = "r" + std::to_string(Keys::GetNumberOfComponents());

	if (!LuaManager::GetComponent(componentType))
	{
		GE_ERROR("Failed to locate component " + componentType);
		return luabridge::newTable(LuaManager::GetLuaState());
	}

	Component* newComponent = new Component();
	newComponent->Type = componentType;
	newComponent->Key = key;
	AddComponent(newComponent);
	return newComponent->Ref;
}

void Actor::LuaRemoveComponent(luabridge::LuaRef componentRef)
{
	for (Component* component : mComponents)
	{
		if (component->Ref.operator==(componentRef))
		{
			component->Ref["enabled"] = false;
			component->Enabled = false;
			break;
		}
	}
}
