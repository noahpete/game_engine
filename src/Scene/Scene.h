#pragma once

#include <string>
#include <vector>
#include "Actor.h"
#include "Configurator.h"
#include "Scene/SceneSerializer.h"

class SceneSerializer;

class Scene
{
public:
	Scene();
	~Scene();

	static void Update();
	static void LateUpdate();
	static void Reset();

	static std::string& GetName() { return mName; }
	static std::vector<Actor*>& GetActors() { return m_Actors; }

private:
	friend class SceneSerializer;

	static std::string mName;
	static std::vector<Actor*> m_Actors;
	static std::vector<Actor*> m_SavedActors;
	
};

