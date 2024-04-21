#pragma once

#include <fstream>
#include <sstream>
#include "Scene.h"
#include "yaml-cpp/yaml.h"
#include "Configurator.h"

class SceneSerializer
{
public:
	SceneSerializer(Scene* scene)
		: m_Scene(scene) {}

	void Serialize(const std::string& path);
	void SerializeRuntime(const std::string& path);

	void Deserialize(const std::string& path);
	void DeserializeRuntime(const std::string& path);

private:
	Scene* m_Scene;

};

