#include "Application.h"

bool Application::sRunning;
bool Application::sGameRunning;
YAML::Node Configurator::EditorConfig;
YAML::Node Configurator::GameConfig;
YAML::Node Configurator::RenderConfig;

Application::Application()
{
	Configurator::LoadConfigs();

	mRenderer = new Renderer();
	mGui = new Gui();
	mScene = new Scene();
	mLuaManager = new LuaManager();

	sRunning = true;
	sGameRunning = false;
	mPrevGameRunning = false;
}

void Application::Run()
{
	while (sRunning)
	{
		Input();
		Update();
		Render();
	}
}

void Application::Input()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) sRunning = false;

		if (!sGameRunning)
			Gui::Input(&e);
		else
			InputHandler::ProcessEvent(&e);
	}
}

void Application::Update()
{
	OnModeChange();

	if (sGameRunning)
	{
		for (Actor* actor : Scene::GetActors())
			if (!actor->IsInitialized())
				actor->Start();

		InputHandler::Update();
		Scene::Update();

		// Return to Editor mode
		if (InputHandler::GetKey("escape"))
		{
			sGameRunning = false;
			InputHandler::ResetKeys();
			Scene::Reset();
		}

		InputHandler::LateUpdate();
		Scene::LateUpdate();

		Physics::GetWorld()->Step(1.0f / 60.0f, 8, 3);
	}

}

void Application::Render()
{
	// Editor mode
	mRenderer->StartFrame();
	mRenderer->RenderFrame();
	mRenderer->CleanupFrame();
}

void Application::OnModeChange()
{
	bool modeChanged = (sGameRunning != mPrevGameRunning);
	if (modeChanged)
	{
		// Editor -> Game
		if (sGameRunning)
		{
			SDL_ShowWindow(Renderer::GetGameWindow());
		}

		// Game -> Editor
		else
		{
			SDL_HideWindow(Renderer::GetGameWindow());
		}
	}
	mPrevGameRunning = sGameRunning;
}
