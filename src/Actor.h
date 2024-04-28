 #pragma once

#include <string>
#include <vector>
#include "lua/lua.hpp"
#include "luabridge/LuaBridge.h"
#include "LuaManager.h"
#include "Component.h"
#include "Keys.h"

class Component;
class LuaManager;

class Actor
{
	friend class TemplateManager;

public:
	luabridge::LuaRef Ref;
	bool mDontDestroy = false;
	bool mEnabled = true;

	Actor(std::string name);

	void Start();
	void Update();
	void LateUpdate();
	void Render();
	void Destroy();
	void UpdateRenderComponents();

	void AddComponent(Component* component);

	std::string& GetName() { return mName; }
	bool IsInitialized() { return mInitialized; }
	std::vector<Component*>& GetComponents() { return mComponents; }

	luabridge::LuaRef LuaGetComponent(std::string type);
	luabridge::LuaRef LuaGetComponents(std::string type);
	luabridge::LuaRef LuaAddComponent(std::string componentType);
	void LuaRemoveComponent(luabridge::LuaRef componentRef);

private:
	bool mInitialized = false;
	std::string mName = "";
	std::vector<Component*> mComponents;

};

