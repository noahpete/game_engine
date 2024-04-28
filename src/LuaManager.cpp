#include "LuaManager.h"

lua_State* LuaManager::sL;
std::unordered_map<std::string, Component*> LuaManager::sComponentDb;

LuaManager::LuaManager()
{
	sL = luaL_newstate();
	luaL_openlibs(sL);

	AddNamespaces();

	LoadComponents();
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

	// Actor class
	luabridge::getGlobalNamespace(sL)
		.beginClass<Actor>("Actor")
		.addFunction("GetName", &Actor::GetName)
		.addFunction("GetComponent", &Actor::LuaGetComponent)
		.addFunction("GetComponents", &Actor::LuaGetComponents)
		.addFunction("AddComponent", &Actor::LuaAddComponent)
		.addFunction("RemoveComponent", &Actor::LuaRemoveComponent)
		.endClass();

	// Actor namespace
	luabridge::getGlobalNamespace(sL)
		.beginNamespace("Actor")
		.addFunction("Find", &Scene::LuaFind)
		.addFunction("FindAll", &Scene::LuaFindAll)
		.addFunction("Instantiate", &Scene::LuaInstantiate)
		.addFunction("Destroy", &Scene::LuaDestroy)
		.endNamespace();

	luabridge::getGlobalNamespace(sL)
		.beginNamespace("Application")
		.addFunction("GetFrame", &FrameCounter::GetFrameNumber)
		.endNamespace();

	// Input
	luabridge::getGlobalNamespace(sL)
		.beginNamespace("Input")
		.addFunction("GetKey", InputHandler::GetKey)
		.addFunction("GetKeyDown", InputHandler::GetKeyDown)
		.addFunction("GetKeyUp", InputHandler::GetKeyUp)
		.addFunction("GetMousePosition", InputHandler::GetMousePosition)
		.addFunction("GetMouseButton", InputHandler::GetMouseButton)
		.addFunction("GetMouseButtonDown", InputHandler::GetMouseButtonDown)
		.addFunction("GetMouseButtonUp", InputHandler::GetMouseButtonUp)
		.addFunction("GetMouseScrollDelta", InputHandler::GetMouseScrollDelta)
		.endNamespace();

	// glm vec2
	luabridge::getGlobalNamespace(sL)
		.beginClass<glm::vec2>("vec2")
		.addConstructor<void (*) (float, float)>()
		.addData("x", &glm::vec2::x)
		.addData("y", &glm::vec2::y)
		.endClass();

	// Audio

	// Text
	luabridge::getGlobalNamespace(LuaManager::GetLuaState())
		.beginNamespace("Text")
		.addFunction("Draw", &RenderRequest::TextDraw)
		.endNamespace();

	// Image
	luabridge::getGlobalNamespace(sL)
		.beginNamespace("Image")
		.addFunction("DrawUI", &RenderRequest::ImageDrawUI)
		.addFunction("DrawUIEx", &RenderRequest::ImageDrawUIEx)
		.addFunction("Draw", &RenderRequest::ImageDraw)
		.addFunction("DrawEx", &RenderRequest::ImageDrawEx)
		.addFunction("DrawPixel", &RenderRequest::ImageDrawPixel)
		.endNamespace();

	// Camera
	luabridge::getGlobalNamespace(sL)
		.beginNamespace("Camera")
		.addFunction("SetPosition", &Camera::SetPosition)
		.addFunction("GetPositionX", &Camera::GetPositionX)
		.addFunction("GetPositionY", &Camera::GetPositionY)
		.addFunction("SetZoom", &Camera::SetZoom)
		.addFunction("GetZoom", &Camera::GetZoom)
		.endNamespace();

	// Scene
	luabridge::getGlobalNamespace(sL)
		.beginNamespace("Scene")
		.addFunction("Load", &Scene::LuaSceneLoad)
		.addFunction("GetCurrent", &Scene::LuaSceneGetCurrent)
		.addFunction("DontDestroy", &Scene::LuaSceneDontDestroy)
		.endNamespace();


}

void LuaManager::LoadComponent(std::string componentType)
{
	std::string path = "assets/components/" + componentType + ".lua";

	if (luaL_dofile(sL, path.c_str()) != LUA_OK)
		GE_ERROR("Problem with Lua file " + componentType);

	Component* component = new Component();
	luabridge::LuaRef parent = luabridge::getGlobal(sL, componentType.c_str());
	EstablishInheritance(component->Ref, parent);
	sComponentDb[componentType] = component;
}

void LuaManager::LoadComponents()
{
	if (std::filesystem::exists("assets/components"))
		for (const auto& componentPath : std::filesystem::directory_iterator("assets/components"))
			LoadComponent(componentPath.path().stem().string());
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

