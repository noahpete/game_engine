#pragma once

#include <string>
#include "lua/lua.hpp"
#include "luabridge/LuaBridge.h"
#include "Actor.h"
#include "Util.h"

class Actor;

class Component
{
public:
	bool mEnabled = true;
	bool mInitialized = false;
	std::string mType;
	luabridge::LuaRef mRef;
	Actor* mParent = nullptr;

	Component(std::string type)
		: mType(type), mRef(nullptr) {}
	~Component() {}

	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Destroy();

	luabridge::LuaRef& GetRef() { return mRef; }

};

