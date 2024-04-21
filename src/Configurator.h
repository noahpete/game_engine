#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "yaml-cpp/yaml.h"

class Configurator
{
public:
    static YAML::Node EditorConfig;
    static YAML::Node GameConfig;
    static YAML::Node RenderConfig;

    static void ReadYamlFile(const std::string& path, YAML::Node& output)
    {
        std::ifstream stream(path);
        std::stringstream strStream;
        strStream << stream.rdbuf();
        output = YAML::Load(strStream.str());
    }

    static void LoadConfigs()
    {
        // Assumes proper formatting of config files (i.e. they contain all necessary data)

        if (std::filesystem::exists(std::filesystem::path("assets/editor.config")))
            ReadYamlFile("assets/editor.config", EditorConfig);
        else
            ReadYamlFile("default/editor.config", EditorConfig);

        if (std::filesystem::exists(std::filesystem::path("assets/game.config")))
            ReadYamlFile("assets/game.config", GameConfig);
        else
            ReadYamlFile("default/game.config", GameConfig);

        if (std::filesystem::exists(std::filesystem::path("assets/render.config")))
            ReadYamlFile("assets/render.config", RenderConfig);
        else
            ReadYamlFile("default/render.config", RenderConfig);
    }
};