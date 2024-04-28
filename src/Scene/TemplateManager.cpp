#include "TemplateManager.h"

std::unordered_map<std::string, YAML::Node> TemplateManager::sTemplates;

void TemplateManager::ApplyTemplate(std::string templateName, Actor* actor)
{
	YAML::Node templateNode = sTemplates[templateName];

	GE_CORE_ASSERT(templateNode, "Template node is invalid!");

	if (templateNode["name"])
		actor->mName = templateNode["name"].as<std::string>();

	if (templateNode["components"])
	{
		for (const auto& pair : templateNode["components"])
		{
			std::string componentName = pair.first.as<std::string>();
			std::string componentType = pair.second["type"].as<std::string>();
			auto component = pair.second;

			Component* newComponent = new Component();
			newComponent->Type = componentType;
			newComponent->Key = componentName;
			actor->AddComponent(newComponent);

			Keys::AddComponent(componentName, newComponent);

			luabridge::LuaRef& ref = newComponent->Ref;

			for (const auto& compPair : component)
			{
				if (SceneSerializer::IsBool(compPair.second))
					ref[compPair.first.as<std::string>()] = compPair.second.as<bool>();

				if (SceneSerializer::IsInt(compPair.second))
					ref[compPair.first.as<std::string>()] = compPair.second.as<int>();

				if (SceneSerializer::IsFloat(compPair.second))
					ref[compPair.first.as<std::string>()] = compPair.second.as<float>();

				if (SceneSerializer::IsString(compPair.second))
					ref[compPair.first.as<std::string>()] = compPair.second.as<std::string>();
			}
		}
	}
}

void TemplateManager::LoadTemplates()
{
	std::string templatesPath = "assets/templates";
	if (std::filesystem::exists(templatesPath))
	{
		auto templates = std::filesystem::directory_iterator(templatesPath);
		for (const auto temp : templates)
			Configurator::ReadYamlFile(temp.path().string(), sTemplates[temp.path().stem().string()]);
	}
}
