#pragma once

#include <memory>
#include "SDL2/SDL.h"
#include "Configurator.h"
#include "InputHandler.h"
#include "LuaManager.h"
#include "Render/Renderer.h"
#include "Editor/Gui.h"
#include "Scene/Scene.h"
#include "FrameCounter.h"
#include "Render/Camera.h"

class Renderer;
class LuaManager;

class Application
{
public:
	static bool sRunning;
	static bool sGameRunning;
	static int sFrameNumber;

	Application();
	~Application() {}

	void Run();
	void Input();
	void Update();
	void Render();
	void OnModeChange();

	static int GetFrameNumber() { return sFrameNumber; }

private:
	bool mPrevGameRunning;
	Renderer* mRenderer;
	Gui* mGui;
	Scene* mScene;
	Scene* mSavedScene;
	LuaManager* mLuaManager;

};

