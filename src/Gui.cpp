#include "Gui.h"

void Gui::Input(SDL_Event* e)
{
	ImGui_ImplSDL2_ProcessEvent(e);
}

void Gui::ShowViewport()
{
	ImGui::Begin("Viewport");

	ImGui::End();
}

void Gui::ShowActors()
{
	ImGui::Begin("Actors");

	ImGui::End();
}

void Gui::ShowProperties()
{
	ImGui::Begin("Properties");

	ImGui::End();
}
