#pragma once

#include <string>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer2.h"
#include "SDL2/SDL.h"
#include "Scene/Scene.h"

class Gui
{
public:
	Gui() {}
	~Gui() {}

	static void Input(SDL_Event* e);
	static void ShowViewport(SDL_Texture* frameTexture);
	static void ShowActors();
	static void ShowProperties();
	static void ShowControls(bool& gameRunning);

private:
	 static Actor* sSelectedActor;

};

