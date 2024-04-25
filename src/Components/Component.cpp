#include "Component.h"

class Custom;
class Physics;
class Sprite;
class Transform;

void Component::Start()
{

	luabridge::LuaRef onStartFunc = mRef["OnStart"];
	if (!onStartFunc.isNil() && onStartFunc.isFunction()) {
		try {
			onStartFunc(mRef);
		}
		catch (luabridge::LuaException& e) {
			GE_ERROR(e.what());
		}
	}
}

void Component::Update()
{
	/*if (mRef["OnUpdate"].isFunction())
	{
		try
		{
			mRef["OnUpdate"](mRef);
		}
		catch (luabridge::LuaException& e)
		{
			GE_ERROR(e.what());
		}
	}*/
}

void Component::LateUpdate()
{
	/*if (mRef["OnLateUpdate"].isFunction())
	{
		try
		{
			mRef["OnLateUpdate"](mRef);
		}
		catch (luabridge::LuaException& e)
		{
			GE_ERROR(e.what());
		}
	}*/
}

void Component::Destroy()
{
	//mEnabled = false;
	//mRef["enabled"] = false;
}
