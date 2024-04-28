#pragma once

#include <filesystem>
#include <unordered_map>
#include "lua/lua.hpp"
#include "luabridge/LuaBridge.h"
#include "InputHandler.h"
#include "Actor.h"
#include "Component.h"
#include "Render/RenderRequest.h"
#include "Render/Camera.h"
#include "FrameCounter.h"
#include "Scene/Scene.h"

class Component;
class Actor;

class LuaManager
{
public:
	LuaManager();
	~LuaManager();

	void AddNamespaces();
	void LoadComponent(std::string componentType);
	void LoadComponents();
	static void EstablishInheritance(luabridge::LuaRef& instance, luabridge::LuaRef& parent);

	static lua_State* GetLuaState() { return sL; }
	static Component* GetComponent(std::string type) { return sComponentDb[type]; }

	static void Log(const std::string& text);
	static void LogErr(const std::string& text);
	static void Quit();

	// TODO: make separate Lua subclasses: LuaInput, LuaApplication, LuaActor, etc.

private:
	static lua_State* sL;
	static std::unordered_map<std::string, Component*> sComponentDb;
};

