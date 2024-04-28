#pragma once

#include <fstream>
#include <sstream>
#include "Scene/Scene.h"
#include "yaml-cpp/yaml.h"
#include "Configurator.h"
#include "Scene/Scene.h"
#include "Scene/TemplateManager.h"
#include "Keys.h"

class Scene;
class TemplateManager;

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

	static bool IsBool(YAML::Node node);
	static bool IsInt(YAML::Node node);
	static bool IsFloat(YAML::Node node);
	static bool IsString(YAML::Node node);

private:
	Scene* mScene;

};

