#include "Scene.h"

std::string Scene::mName;
std::vector<Actor*> Scene::m_Actors;

Scene::Scene()
{
	std::string scenePath = "assets/scenes/sandbox.scene";
	SceneSerializer serializer(this);
	serializer.Deserialize(scenePath);
}

Scene::~Scene()
{
}

void Scene::Update()
{
 	for (Actor* actor : m_Actors)
		actor->Update();
}

void Scene::LateUpdate()
{
	for (Actor* actor : m_Actors)
		actor->LateUpdate();
}

void Scene::Reset()
{
	Scene();
}
