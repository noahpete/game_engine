#pragma once

#include <fstream>
#include <sstream>
#include "Scene/Scene.h"
#include "yaml-cpp/yaml.h"
#include "Configurator.h"
#include "Components/Components.h"
#include "Scene/Scene.h"

class Scene;

class SceneSerializer
{
public:
	SceneSerializer(Scene* scene)
		: mScene(scene) {}

	void Serialize(const std::string& path);
	void SerializeRuntime(const std::string& path);
	void SerializeActor(YAML::Emitter& out, Actor* actor);

	void Deserialize(const std::string& path);
	void DeserializeRuntime(const std::string& path);

private:
	Scene* mScene;

};

