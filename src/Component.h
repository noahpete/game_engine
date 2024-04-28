#pragma once

#include <string>
#include "lua/lua.hpp"
#include "luabridge/LuaBridge.h"
#include "LuaManager.h"
#include "Util.h"

class Actor;
class LuaManager;

class Component
{
public:
	luabridge::LuaRef Ref;
	std::string Type = "None";
	std::string Key = "DefaultKey";
	bool Enabled = true;
	bool Initialized = false;

	Component();
	~Component();

	void Start();
	void Update();
	void LateUpdate();
	void Render();
	void Destroy();

};

