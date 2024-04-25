#pragma once

#include <memory>
#include "SDL2/SDL.h"
#include "Configurator.h"
#include "InputHandler.h"
#include "Components/Physics.h"
#include "LuaManager.h"
#include "Render/Renderer.h"
#include "Render/Gui.h"
#include "Scene/Scene.h"

class Renderer;

class Application
{
public:
	static bool sRunning;
	static bool sGameRunning;

	Application();
	~Application() {}

	void Run();
	void Input();
	void Update();
	void Render();
	void OnModeChange();

private:
	bool mPrevGameRunning;
	Renderer* mRenderer;
	Gui* mGui;
	Scene* mScene;
	LuaManager* mLuaManager;

};

