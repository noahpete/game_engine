#include "Application.h"

bool State::sRunning;
bool State::sGameRunning;
int State::sFrameNumber;
YAML::Node Configurator::EditorConfig;
YAML::Node Configurator::GameConfig;
YAML::Node Configurator::RenderConfig;


Application::Application()
{
	Audio::PlayAudio(1, "mission_start_vocal", false);
	Configurator::LoadConfigs();

	mRenderer = new Renderer();
	mLuaManager = new LuaManager();
	mGui = new Gui();
	mScene = new Scene();
	mAudio = new Audio();

	FrameCounter::Reset();

	State::sRunning = true;
	State::sGameRunning = false;
	mPrevGameRunning = false;
}

void Application::Run()
{
	while (State::sRunning)
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
		if (e.type == SDL_QUIT) State::sRunning = false;

		if (!State::sGameRunning)
			Gui::Input(&e);
		else
			InputHandler::ProcessEvent(&e);
	}
}

void Application::Update()
{
	OnModeChange();

	if (State::sGameRunning)
	{
		for (Actor* actor : Scene::GetActors())
			if (!actor->IsInitialized())
				actor->Start();

		InputHandler::Update();
		Scene::Update();

		// Return to Editor mode
		if (InputHandler::GetKey("escape"))
		{
			State::sGameRunning = false;
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
	bool modeChanged = (State::sGameRunning != mPrevGameRunning);
	if (modeChanged)
	{
		// Editor -> Game
		if (State::sGameRunning)
		{
			FrameCounter::Reset();
			Scene::UninitializeActors(); // uninitialize actors so Start is called on game start
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
	mPrevGameRunning = State::sGameRunning;
}
