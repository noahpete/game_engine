#include "Application.h"

bool Application::sRunning;
bool Application::sGameRunning;
int Application::sFrameNumber;
YAML::Node Configurator::EditorConfig;
YAML::Node Configurator::GameConfig;
YAML::Node Configurator::RenderConfig;


Application::Application()
{
	Configurator::LoadConfigs();

	mRenderer = new Renderer();
	mLuaManager = new LuaManager();
	mGui = new Gui();
	mScene = new Scene();

	FrameCounter::Reset();

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
			return;
		}

		InputHandler::LateUpdate();
		Scene::LateUpdate();

		//GE_CORE_INFO("Frame: " + std::to_string(FrameCounter::GetFrameNumber()));
		FrameCounter::Increment();
	}

	Scene::Render();
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
			mSavedScene = mScene;
			FrameCounter::Reset();
			SDL_ShowWindow(Renderer::GetGameWindow());
		}

		// Game -> Editor
		else
		{
			Scene::Reset();
			Camera::Reset(); // TODO: make it so state is saved then retrieved   

			SceneSerializer serializer(mScene);
			std::string path = "assets/scenes/" + mScene->GetName() + ".scene";
			serializer.Deserialize(path);

			InputHandler::ResetKeys();
			SDL_HideWindow(Renderer::GetGameWindow());
		}
	}
	mPrevGameRunning = sGameRunning;
}
