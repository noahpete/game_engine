#include "SceneSerializer.h"

void SceneSerializer::Serialize(const std::string& path)
{
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "name" << YAML::Value << mScene->GetName();

	out << YAML::Key << "actors" << YAML::Value << YAML::BeginSeq;
	for (Actor* actor : mScene->GetActors())
		SerializeActor(out, actor);
	out << YAML::EndSeq;
	out << YAML::EndMap;

	std::ofstream fout(path);
	fout << out.c_str();
}

void SceneSerializer::SerializeRuntime(const std::string& path)
{
}

void SceneSerializer::SerializeActor(YAML::Emitter& out, Actor* actor)
{
	out << YAML::BeginMap;
	out << YAML::Key << "name" << YAML::Value << actor->GetName();

	out << YAML::Key << "components" << YAML::Value << YAML::BeginMap;

	for (Component* component : actor->GetComponents())
	{
		
	}

	out << YAML::EndMap;
	out << YAML::EndMap;
}

void SceneSerializer::Deserialize(const std::string& path)
{
	YAML::Node data;
	Configurator::ReadYamlFile(path, data);

	for (const auto& actor : data["actors"])
	{
		std::string name = "";
		std::string templateName = "";

		if (actor["name"])
			name = actor["name"].as<std::string>();

		if (actor["template"])
			templateName = actor["template"].as<std::string>();

		Actor* deserialized = new Actor(name);

		// TODO: apply template to deserialized (before overriding variables)
		if (templateName != "")
			TemplateManager::ApplyTemplate(templateName, deserialized);

		for (const auto& pair : actor["components"])
		{
 			std::string componentName = pair.first.as<std::string>();
			std::string componentType = pair.second["type"].as<std::string>();
			auto component = pair.second;

			Component* newComponent = new Component();
			newComponent->Type = componentType;
			newComponent->Key = componentName;
			deserialized->AddComponent(newComponent);
			
			Keys::AddComponent(componentName, newComponent);

			luabridge::LuaRef& ref = newComponent->Ref;

			for (const auto& compPair : component)
			{
				// Order of checking matters...

				if (IsString(compPair.second))
 					ref[compPair.first.as<std::string>()] = compPair.second.as<std::string>();

				if (IsInt(compPair.second))
					ref[compPair.first.as<std::string>()] = compPair.second.as<int>();

				if (IsFloat(compPair.second))
					ref[compPair.first.as<std::string>()] = compPair.second.as<float>();

				if (IsBool(compPair.second))
					ref[compPair.first.as<std::string>()] = compPair.second.as<bool>();
			}
		}

		mScene->mActors.push_back(deserialized);
	}


	// Make Actors Lua look up table
	luabridge::LuaRef actorsTable = luabridge::newTable(LuaManager::GetLuaState());

	for (Actor* actor : mScene->GetActors())
		actorsTable[actor->GetName()] = actor->Ref;

	luabridge::setGlobal(LuaManager::GetLuaState(), actorsTable, "Actors");
}

void SceneSerializer::DeserializeRuntime(const std::string& path)
{
}

bool SceneSerializer::IsBool(YAML::Node node)
{
	try
	{
		bool value = node.as<bool>();
		return true;
	}
	catch (const YAML::BadConversion& e )
	{
		return false;
	}
}

bool SceneSerializer::IsInt(YAML::Node node)
{
	try
	{
		bool value = node.as<int>();
		return true;
	}
	catch (const YAML::BadConversion& e)
	{
		return false;
	}
}

bool SceneSerializer::IsFloat(YAML::Node node)
{
	try
	{
		bool value = node.as<float>();
		return true;
	}
	catch (const YAML::BadConversion& e)
	{
		return false;
	}
}

bool SceneSerializer::IsString(YAML::Node node)
{
	try
	{
		std::string value = node.as<std::string>();
		return true;
	}
	catch (const YAML::BadConversion& e)
	{
		return false;
	}
}
