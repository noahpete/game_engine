#pragma once

#include <unordered_map>
#include "lua/lua.hpp"
#include "luabridge/LuaBridge.h"
#include "Components/Component.h"
#include "Components/Components.h"

class LuaManager
{
public:
	LuaManager();
	~LuaManager();

	void AddNamespaces();
	void AddDefaultComponentNamespaces();
	void LoadComponent(std::string componentType);
	void EstablishInheritance(luabridge::LuaRef& instance, luabridge::LuaRef& parent);

	template<class T>
	Component* LoadDefaultComponent()
	{
		Component* component = new Component("Default");
		T* t = new T();
		luabridge::LuaRef componentRef(sL, t);
		component->GetRef() = componentRef;
		return component;
	}

	static void Log(const std::string& text);
	static void LogErr(const std::string& text);
	static void Quit();
	static int GetFrame();

private:
	static lua_State* sL;
	static std::unordered_map<std::string, Component*> sComponentDb;
};

