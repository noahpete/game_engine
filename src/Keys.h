#pragma once

#include <string>
#include <unordered_map>

class Actor;
class Component;

static std::unordered_map<std::string, Actor*> sActorKeys;
static std::unordered_map<std::string, Component*> sComponentKeys;

class Keys
{
public:
	static void AddActor(std::string key, Actor* actor) { sActorKeys[key] = actor; }
	static void AddComponent(std::string key, Component* component) { sComponentKeys[key] = component; }

	static Actor* GetActor(std::string key) { return sActorKeys[key]; }
	static Component* GetComponent(std::string key) { return sComponentKeys[key]; }
	static int GetNumberOfComponents() { return sComponentKeys.size(); }

};

