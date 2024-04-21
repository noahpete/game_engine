#include "SceneSerializer.h"

void SceneSerializer::Serialize(const std::string& path)
{
}

void SceneSerializer::SerializeRuntime(const std::string& path)
{
}

void SceneSerializer::Deserialize(const std::string& path)
{
	YAML::Node data;
	Configurator::ReadYamlFile(path, data);

	if (!data["scene"])
		return;

	m_Scene->m_Name = data["scene"].as<std::string>();

	YAML::Node actors = data["actors"];
	if (actors)
	{
		for (auto actor : actors)
		{
			std::string name = "";

			if (actor["name"])
				name = actor["name"].as<std::string>();

			Actor* inputActor = new Actor(name);
		}
	}
}

void SceneSerializer::DeserializeRuntime(const std::string& path)
{
}
