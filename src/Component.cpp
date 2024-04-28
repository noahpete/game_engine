#include "Component.h"

Component::Component()
	: Ref(nullptr)
{
	Ref = luabridge::newTable(LuaManager::GetLuaState());
}

Component::~Component()
{
}

void Component::Start()
{
	if (Initialized || !Enabled) return;

	if (Ref["OnStart"].isFunction())
	{
		try
		{
			Ref["OnStart"](Ref);
		}
		catch (luabridge::LuaException& e)
		{
			GE_ERROR(e.what());
		}
	}

	Initialized = true;
}

void Component::Update()
{
	if (!Enabled || !Initialized) return;

	if (Ref["OnUpdate"].isFunction())
	{
		try
		{
			Ref["OnUpdate"](Ref);
		}
		catch (luabridge::LuaException& e)
		{
			GE_ERROR(e.what());
		}
	}
}

void Component::LateUpdate()
{
	if (!Enabled || !Initialized) return;

	if (Ref["OnLateUpdate"].isFunction())
	{
		try
		{
			Ref["OnLateUpdate"](Ref);
		}
		catch (luabridge::LuaException& e)
		{
			GE_ERROR(e.what());
		}
	}
}

void Component::Render()
{
	if (!Enabled) return;

	if (!Initialized)
		Start();

	if (Ref["OnRender"].isFunction())
	{
		try
		{
			Ref["OnRender"](Ref);
		}
		catch (luabridge::LuaException& e)
		{
			GE_ERROR(e.what());
		}
	}
}

void Component::Destroy()
{
	Enabled = false;
	Ref["enabled"] = false;
	
	if (Ref["OnDestroy"].isFunction())
		Ref["OnDestroy"](Ref);
}
