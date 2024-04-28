#include "Scene.h"

std::string Scene::sNewSceneName;
std::string Scene::sName;
std::vector<Actor*> Scene::mActors;
std::vector<Actor*> Scene::mActorsToDestroy;

Scene::Scene()
{
	sName = "sandbox";
	std::string scenePath = "assets/scenes/" + sName + ".scene";
	TemplateManager::LoadTemplates();
	SceneSerializer serializer(this);
	serializer.Deserialize(scenePath);
	sNewSceneName = "";
}

Scene::~Scene()
{
}

void Scene::Update()
{
	if (sNewSceneName != "")
	{
		sName = sNewSceneName;
		LoadNewScene();
	}

	auto actorsToUpdate = mActors;

	for (Actor* actor : actorsToUpdate)
	{
		if (!actor) continue;
		actor->Update();
	}
}

void Scene::LateUpdate()
{
	for (Actor* actor : mActors)
		actor->LateUpdate();

	for (Actor* actor : mActorsToDestroy)
	{
		actor->Destroy();
	}

	mActorsToDestroy.clear();
}

void Scene::Render()
{
	for (Actor* actor : mActors)
		actor->Render();
}

void Scene::Reset()
{
	mActors.clear();
}

void Scene::LoadNewScene()
{
	std::vector<Actor*> actorsToKeep;

	for (Actor* actor : mActors)
	{
		if (actor->mDontDestroy)
			actorsToKeep.push_back(actor);
	}

	mActors.clear();
	mActors = actorsToKeep;

	sName = sNewSceneName;
	Scene();
}

void Scene::LuaSceneLoad(std::string sceneName)
{
	sNewSceneName = sceneName;
}

void Scene::LuaSceneDontDestroy(luabridge::LuaRef actor)
{
	for (Actor* actor : mActors)
	{
		if (actor->Ref == actor)
		{
			actor->mDontDestroy = true;
			break;
		}
	}
}

std::string Scene::LuaSceneGetCurrent()
{
	return std::string();
}

luabridge::LuaRef Scene::LuaFind(std::string actorName)
{
	for (Actor* actor : mActors)
	{
		if (actor->GetName() == actorName && actor->mEnabled)
			return actor->Ref;
	}
	return luabridge::newTable(LuaManager::GetLuaState());
}

luabridge::LuaRef Scene::LuaFindAll(std::string name)
{
	luabridge::LuaRef actorsTable = luabridge::newTable(LuaManager::GetLuaState());

	for (size_t i = 0; i < mActors.size(); ++i)
	{
		if (mActors[i]->GetName() == name && mActors[i]->mEnabled)
			actorsTable[i] = mActors[i]; // Not sure why 0 indexed here
	}
	return luabridge::newTable(LuaManager::GetLuaState());
}

luabridge::LuaRef Scene::LuaInstantiate(std::string templateName)
{
	GE_INFO("Creating new Actor with template " + templateName);
	Actor* newActor = new Actor(templateName);
	TemplateManager::ApplyTemplate(templateName, newActor);
	mActors.push_back(newActor);
	return newActor->Ref;
}

void Scene::LuaDestroy(Actor* actorRef)
{
	for (Actor* actor : mActors)
	{
        if (actor == actorRef)
		{
			actor->mEnabled = false;
			mActorsToDestroy.push_back(actor);
		}
	}
}
