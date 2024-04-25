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
		auto sc = dynamic_cast<Sprite*>(component);
		if (sc)
		{
			out << YAML::Key << "Sprite" << YAML::Value << YAML::BeginMap;
			out << YAML::Key << "image_name" << YAML::Value << sc->TextureName;
			out << YAML::EndMap;
		}

		auto tc = dynamic_cast<Transform*>(component);
		if (tc)
		{
			out << YAML::Key << "Transform" << YAML::Value << YAML::BeginMap;
			out << YAML::Key << "position_x" << YAML::Value << tc->Position.x;
			out << YAML::Key << "position_y" << YAML::Value << tc->Position.y;
			out << YAML::Key << "scale_x" << YAML::Value << tc->Scale.x;
			out << YAML::Key << "scale_y" << YAML::Value << tc->Scale.y;
			out << YAML::Key << "rotation" << YAML::Value << tc->Rotation;
			out << YAML::EndMap;
		}
	}

	out << YAML::EndMap;
	out << YAML::EndMap;
}

void SceneSerializer::Deserialize(const std::string& path)
{
	YAML::Node data;
	Configurator::ReadYamlFile(path, data);

	mScene->mName = data["name"].as<std::string>();

	for (const auto& actor : data["actors"])
	{
		std::string name = "";
		if (actor["name"])
			name = actor["name"].as<std::string>();

		Actor* deserialized = new Actor(name);

		for (const auto& pair : actor["components"])
		{
 			std::string componentType = pair.first.as<std::string>();
			auto component = pair.second;

			// TODO: add custom Lua components

			if (componentType == "Transform")
			{
				Transform* tc = deserialized->GetOrAddComponent<Transform>();

				if (component["position_x"])
					tc->Position.x = component["position_x"].as<float>();
				if (component["position_y"])
					tc->Position.y = component["position_y"].as<float>();
				if (component["rotation"])
					tc->Rotation = component["rotation"].as<float>();
				if (component["scale_x"])
					tc->Scale.x = component["scale_x"].as<float>();
				if (component["scale_y"])
					tc->Scale.y = component["scale_y"].as<float>();
			}

			if (componentType == "Sprite")
			{
				Sprite* sc = deserialized->GetOrAddComponent<Sprite>();
				if (component["image_name"])
					sc->TextureName = component["image_name"].as<std::string>();
			}

			if (componentType == "Physics")
			{
				Physics* pc = deserialized->GetOrAddComponent<Physics>();
				if (component["body_type"])
					pc->BodyType = component["body_type"].as<std::string>();
				if (component["precise"])
					pc->Precise = component["precise"].as<bool>();
				if (component["density"])
					pc->Density = component["density"].as<float>();
				if (component["gravity_scale"])
					pc->GravityScale = component["gravity_scale"].as<float>();
				if (component["friction"])
					pc->Friction = component["friction"].as<float>();
				if (component["angular_friction"])
					pc->AngularFriction = component["angular_friction"].as<float>();
				if (component["bounciness"])
					pc->Bounciness = component["bounciness"].as<float>();
				if (component["has_collider"])
					pc->HasCollider = component["has_collider"].as<bool>();
				if (pc->HasCollider)
				{
					if (component["collider_type"])
						pc->Collider.Type = component["collider_type"].as<std::string>();
					if (component["collider_width"])
						pc->Collider.Width = component["collider_width"].as<float>();
					if (component["collider_height"])
						pc->Collider.Height = component["collider_height"].as<float>();
					if (component["collider_radius"])
						pc->Collider.Radius = component["collider_radius"].as<float>();
				}
				if (component["has_trigger"])
					pc->HasTrigger = component["has_trigger"].as<bool>();
				if (pc->HasTrigger)
				{
					if (component["trigger_type"])
						pc->Trigger.Type = component["trigger_type"].as<std::string>();
					if (component["trigger_width"])
						pc->Trigger.Width = component["trigger_width"].as<float>();
					if (component["trigger_height"])
						pc->Trigger.Height = component["trigger_height"].as<float>();
					if (component["trigger_radius"])
						pc->Trigger.Radius = component["trigger_radius"].as<float>();
				}
			}

			// Add more built-in components...
		}

		mScene->m_Actors.push_back(deserialized);
	}
}

void SceneSerializer::DeserializeRuntime(const std::string& path)
{
}
