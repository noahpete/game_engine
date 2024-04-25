#include "LuaManager.h"

lua_State* LuaManager::sL;
std::unordered_map<std::string, Component*> LuaManager::sComponentDb;

LuaManager::LuaManager()
{
	sL = luaL_newstate();
	luaL_openlibs(sL);

	AddNamespaces();

	// Load default components
	Component* transformComponent = LoadDefaultComponent<Transform>();
	sComponentDb["Transform"] = transformComponent;

	Component* physicsComponent = LoadDefaultComponent<Physics>();
	sComponentDb["Physics"] = physicsComponent;

	Component* spriteComponent = LoadDefaultComponent<Sprite>();
	sComponentDb["Sprite"] = spriteComponent;
}

LuaManager::~LuaManager()
{
}

void LuaManager::AddNamespaces()
{
	luabridge::getGlobalNamespace(sL)
		.beginNamespace("Debug")
		.addFunction("Log", Log)
		.addFunction("LogError", LogErr)
		.endNamespace();

	luabridge::getGlobalNamespace(sL)
		.beginClass<Actor>("Actor")
		.addFunction("GetName", &Actor::GetName)
		/*.addFunction("GetID", &Actor::GetID)
		.addFunction("GetComponentByKey", &Actor::GetComponentByKey)
		.addFunction("GetComponent", &Actor::GetComponent)
		.addFunction("GetComponents", &Actor::GetComponents)
		.addFunction("AddComponent", &Actor::LuaAddComponent)
		.addFunction("RemoveComponent", &Actor::LuaRemoveComponent)*/
		.endClass();

	AddDefaultComponentNamespaces();

}

void LuaManager::AddDefaultComponentNamespaces()
{
	luabridge::getGlobalNamespace(sL)
		.beginClass<Transform>("Transform")
		.addData("rotation", &Transform::Rotation)
		.addData("position", &Transform::Position)
		.addData("scale", &Transform::Scale)
		.addFunction("OnStart", &Transform::Start)
		.endClass();

	luabridge::getGlobalNamespace(sL)
		.beginClass<Physics>("Physics")
		.addData("body_type", &Physics::BodyType)
		.addData("has_collider", &Physics::HasCollider)
		.addData("has_trigger", &Physics::HasTrigger)
		.addData("density", &Physics::Density)
		.addData("gravity_scale", &Physics::GravityScale)
		.addData("friction", &Physics::Friction)
		.addData("angular_friction", &Physics::AngularFriction)
		.addData("bounciness", &Physics::Bounciness)
		.endClass();

	luabridge::getGlobalNamespace(sL)
		.beginClass<Sprite>("Sprite")
		.addData("texture_name", &Sprite::TextureName)
		.endClass();

}

void LuaManager::LoadComponent(std::string componentType)
{
	std::string path = "assets/components/" + componentType + ".lua";

	if (luaL_dofile(sL, path.c_str()) != LUA_OK)
		GE_ERROR("Problem with Lua file " + componentType);

	Component* component = new Component("None");
	luabridge::LuaRef parent = luabridge::getGlobal(sL, componentType.c_str());
	EstablishInheritance(component->GetRef(), parent);
	sComponentDb[componentType] = component;
}

void LuaManager::EstablishInheritance(luabridge::LuaRef& instance, luabridge::LuaRef& parent)
{
	luabridge::LuaRef newMetatable = luabridge::newTable(sL);
	newMetatable["__index"] = parent;

	instance.push(sL);
	newMetatable.push(sL);
	lua_setmetatable(sL, -2);
	lua_pop(sL, 1);
}

void LuaManager::Log(const std::string& text)
{
	GE_INFO(text);
}

void LuaManager::LogErr(const std::string& text)
{
	GE_ERROR(text);
}

void LuaManager::Quit()
{
	
}

int LuaManager::GetFrame()
{
	return 0;
}
