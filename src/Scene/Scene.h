#pragma once

#include <string>
#include <vector>
#include "Actor.h"
#include "Configurator.h"
#include "Scene/SceneSerializer.h"
#include "Scene/TemplateManager.h"

class SceneSerializer;

class Scene
{
public:
	Scene();
	~Scene();

	static void Update();
	static void LateUpdate();
	static void Render();
	static void Reset();
	static void LoadNewScene();

	static void LuaSceneLoad(std::string sceneName);
	static void LuaSceneDontDestroy(luabridge::LuaRef actor);
	static std::string LuaSceneGetCurrent();

	static std::string& GetName() { return sName; }
	static std::vector<Actor*>& GetActors() { return mActors; }

	static luabridge::LuaRef LuaFind(std::string actorName);
	static luabridge::LuaRef LuaFindAll(std::string);
	static luabridge::LuaRef LuaInstantiate(std::string templateName);
	static void LuaDestroy(Actor* actorRef);

private:
	friend class SceneSerializer;

	static std::string sName;
	static std::vector<Actor*> mActors;
	static std::vector<Actor*> mSavedActors;
	static std::vector<Actor*> mActorsToDestroy;

	static std::string sNewSceneName;
	
};

