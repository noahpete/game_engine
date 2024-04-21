#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer2.h"
#include "SDL2/SDL.h"

class Gui
{
public:
	Gui() {}
	~Gui() {}

	static void Input(SDL_Event* e);
	static void ShowViewport();
	static void ShowActors();
	static void ShowProperties();

private:
	// static Actor* m_SelectedActor;

};

