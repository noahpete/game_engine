#include "Gui.h"

Actor* Gui::sSelectedActor;

void Gui::Input(SDL_Event* e)
{
	ImGui_ImplSDL2_ProcessEvent(e);
}

void Gui::ShowViewport(SDL_Texture* frameTexture)
{
	int width, height;
	SDL_QueryTexture(frameTexture, NULL, NULL, &width, &height);

	ImGui::Begin("Viewport");
	ImGui::Text("pointer = %p", frameTexture);
	ImGui::Text("size = %d x %d", width, height);
	ImGui::Image((void*)frameTexture, ImVec2(width, height));
	ImGui::End();
}

void Gui::ShowActors()
{
	ImGui::Begin("Actors");

	for (Actor* actor : Scene::GetActors())
	{
		bool isSelected = (actor == sSelectedActor);
		if (ImGui::Selectable(actor->GetName().c_str(), isSelected))
			sSelectedActor = actor;
	}

	ImGui::End();
}

void Gui::ShowProperties()
{
	ImGui::Begin("Properties");

	if (!sSelectedActor)
	{
		ImGui::End();
		return;
	}

	ImGui::SeparatorText("Components");

    for (Component* component : sSelectedActor->GetComponents())
    {
        ImGuiTreeNodeFlags comp_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen;

        if (ImGui::TreeNodeEx(component->mType.c_str(), comp_flags))
        {
            //if (component->ref_["type"].isString())
            //    ImGui::Text("Type: %s", component->ref_["type"].cast<std::string>().c_str());

            //for (luabridge::Iterator iter(comp->ref_); !iter.isNil(); ++iter)
            //{
            //    luabridge::LuaRef key = iter.key();
            //    luabridge::LuaRef value = iter.value();

            //    if (key.cast<std::string>() == "type" || key.cast<std::string>() == "key")
            //        continue;

            //    if (key.isString())
            //    {
            //        if (value.isNumber())
            //        {
            //            float num = value.cast<float>();
            //            ImGui::DragFloat(key.cast<std::string>().c_str(), &num, 1.0f);
            //            component->ref_[key] = num;
            //        }
            //        else if (value.isString())
            //        {
            //            std::string str = value.cast<std::string>();
            //            static char buffer[256] = { 0 };
            //            strncpy_s(buffer, str.c_str(), sizeof(buffer) - 1);

            //            if (ImGui::InputText(key.cast<std::string>().c_str(), buffer, sizeof(buffer)))
            //                component->ref_[key] = std::string(buffer);
            //        }
            //        else if (value.isBool())
            //        {
            //            bool b = value.cast<bool>();
            //            ImGui::Checkbox(key.cast<std::string>().c_str(), &b);
            //            component->ref_[key] = b;
            //        }
            //        else if (value.isTable()) {
            //            // Handle nested tables
            //        }
            //    }
            //}

            ImGui::TreePop();
        }
    }


	ImGui::End();
}

void Gui::ShowControls(bool& gameRunning)
{
	ImGui::Begin("Game Controls");

	std::string status;
	if (gameRunning) status = "Status: Running";
	else status = "Status: Stopped";

	ImGui::Text(status.c_str());
	ImGui::SameLine();

	if (ImGui::Button("Play"))
	{

		gameRunning = true;
	}

	ImGui::End();
}
