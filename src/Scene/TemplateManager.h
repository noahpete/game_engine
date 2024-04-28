#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include "yaml-cpp/yaml.h"
#include "Actor.h"
#include "Configurator.h"
#include "Scene/SceneSerializer.h"

class SceneSerializer;

class TemplateManager
{
public:
	static YAML::Node GetTemplate(std::string templateName) { return sTemplates[templateName]; }
	static void ApplyTemplate(std::string templateName, Actor* actor);
	static void LoadTemplates();

private:
	static std::unordered_map<std::string, YAML::Node> sTemplates;

};

