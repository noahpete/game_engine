#pragma once

#include <string>
#include <vector>
#include "Actor.h"

class SceneSerializer;

class Scene
{
public:
	Scene() {}
	~Scene() {}

private:
	friend class SceneSerializer;

	static std::string m_Name;
	static std::vector<Actor*> m_Actors;
	
};

