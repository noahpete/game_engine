#include "Renderer.h"

SDL_Window* Renderer::m_EditorWindow;
SDL_Window* Renderer::m_GameWindow;
SDL_Renderer* Renderer::m_EditorRenderer;
SDL_Renderer* Renderer::m_GameRenderer;
std::unordered_map<std::string, SDL_Texture*> Renderer::m_Textures;

Renderer::Renderer()
{
	m_EditorWindowSize.x = Configurator::EditorConfig["x_resolution"].as<int>();
	m_EditorWindowSize.y = Configurator::EditorConfig["y_resolution"].as<int>();
	m_EditorClearColor.r = Configurator::EditorConfig["clear_color_r"].as<int>();
	m_EditorClearColor.g = Configurator::EditorConfig["clear_color_g"].as<int>();
	m_EditorClearColor.b = Configurator::EditorConfig["clear_color_b"].as<int>();

	m_GameWindowSize.x = Configurator::RenderConfig["x_resolution"].as<int>();
	m_GameWindowSize.y = Configurator::RenderConfig["y_resolution"].as<int>();
	m_GameClearColor.r = Configurator::RenderConfig["clear_color_r"].as<int>();
	m_GameClearColor.g = Configurator::RenderConfig["clear_color_g"].as<int>();
	m_GameClearColor.b = Configurator::RenderConfig["clear_color_b"].as<int>();

	m_EditorWindow = SDL_CreateWindow("Noah's Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_EditorWindowSize.x, m_EditorWindowSize.y, SDL_WINDOW_SHOWN);
	m_EditorRenderer = SDL_CreateRenderer(m_EditorWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	m_GameWindow = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_GameWindowSize.x, m_GameWindowSize.y, SDL_WINDOW_HIDDEN);
	m_GameRenderer = SDL_CreateRenderer(m_GameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	IMG_Init(IMG_INIT_PNG);
	//TTF_Init();

	LoadTextures();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplSDL2_InitForSDLRenderer(m_EditorWindow, m_EditorRenderer);
	ImGui_ImplSDLRenderer2_Init(m_EditorRenderer);
}

Renderer::~Renderer()
{
}

void Renderer::LoadTextures()
{
	std::string texturesPath = "assets/textures";
	auto textures = std::filesystem::directory_iterator(texturesPath);
	for (const auto& texture : textures)
	{
		std::string textureName = texture.path().stem().string();
		SDL_Texture* tex = IMG_LoadTexture(m_GameRenderer, texture.path().string().c_str());
		m_Textures[textureName] = tex;
	}
}

void Renderer::Update()
{
}

void Renderer::StartFrame()
{
	SDL_SetRenderDrawColor(m_EditorRenderer, m_EditorClearColor.r, m_EditorClearColor.g, m_EditorClearColor.b, 255);
	SDL_RenderClear(m_EditorRenderer);

	SDL_SetRenderDrawColor(m_GameRenderer, m_GameClearColor.r, m_GameClearColor.g, m_GameClearColor.b, 255);
	SDL_RenderClear(m_GameRenderer);
}

void Renderer::RenderFrame()
{
	RenderScene();
	RenderUI();
	RenderGui();

	if (!Application::sGameRunning)
	{
		RenderGameToBmp();
		SDL_RenderPresent(m_EditorRenderer);
	}
	else
		RenderGameToScreen();
}

void Renderer::CleanupFrame()
{
}

void Renderer::RenderGui()
{
	if (Application::sGameRunning) return;

	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	Gui::ShowViewport(IMG_LoadTexture(m_EditorRenderer, "frame.bmp"));
	Gui::ShowActors();
	Gui::ShowProperties();
	Gui::ShowControls(Application::sGameRunning);
	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::RenderScene()
{
	std::vector<RenderRequest::ImageDrawRequest> imageRequests;

	while (!RenderRequest::GetImageDrawRequests().empty())
	{
		imageRequests.push_back(RenderRequest::GetImageDrawRequests().front());
		RenderRequest::GetImageDrawRequests().pop();
	}

	std::stable_sort(imageRequests.begin(), imageRequests.end(),
		[](const RenderRequest::ImageDrawRequest& a, const RenderRequest::ImageDrawRequest& b)
		{
			return a.sortingOrder < b.sortingOrder;
		});

	for (const RenderRequest::ImageDrawRequest& request : imageRequests)
	{
		// Units are scene space until render in SDL_RenderCopyEx

		float cameraZoom = Camera::GetZoom();

		SDL_RenderSetScale(m_GameRenderer, cameraZoom, cameraZoom);

		SDL_Texture* texture = m_Textures[request.imageName];
		SDL_Rect target;
		SDL_QueryTexture(texture, NULL, NULL, &target.w, &target.h);

		target.w = int(target.w * request.scaleX);
		target.h = int(target.h * request.scaleY);

		target.x = request.x * 100 + int(m_GameWindowSize.x * 0.5 / cameraZoom) - int(request.pivotX * target.w);
		target.y = request.y * 100 + int(m_GameWindowSize.y * 0.5 / cameraZoom) - int(request.pivotY * target.h);

		target.x -= Camera::GetPositionX() * 100;
		target.y -= Camera::GetPositionY() * 100;

		SDL_Point pivot = { int(request.pivotX * target.w * request.scaleX), int(request.pivotY * target.h * request.scaleY) };

		SDL_SetTextureAlphaMod(texture, static_cast<uint8_t>(request.a));
		SDL_SetTextureColorMod(texture, static_cast<uint8_t>(request.r), static_cast<uint8_t>(request.g), static_cast<uint8_t>(request.b));

		SDL_RenderCopyEx(m_GameRenderer, texture, NULL, &target, request.rotationDegrees, &pivot, SDL_FLIP_NONE);
	}
}

void Renderer::RenderUI()
{
	std::vector<RenderRequest::ImageDrawRequest> UIRequests;

	while (!RenderRequest::GetUIDrawRequests().empty())
	{
		UIRequests.push_back(RenderRequest::GetUIDrawRequests().front());
		RenderRequest::GetUIDrawRequests().pop();
	}

	std::stable_sort(UIRequests.begin(), UIRequests.end(),
		[](const RenderRequest::ImageDrawRequest& a, const RenderRequest::ImageDrawRequest& b)
		{
			return a.sortingOrder < b.sortingOrder;
		});

	for (const RenderRequest::ImageDrawRequest& request : UIRequests)
	{
		SDL_RenderSetScale(m_GameRenderer, 1.0f, 1.0f);

		SDL_Texture* texture = m_Textures[request.imageName];

		SDL_Rect target;
		SDL_QueryTexture(texture, NULL, NULL, &target.w, &target.h);

		target.x = request.x;
		target.y = request.y;

		SDL_Point pivot = { int(request.pivotX), int(request.pivotY) };

		SDL_SetTextureAlphaMod(texture, static_cast<uint8_t>(request.a));
		SDL_SetTextureColorMod(texture, static_cast<uint8_t>(request.r), static_cast<uint8_t>(request.g), static_cast<uint8_t>(request.b));

		SDL_RenderCopyEx(m_GameRenderer, texture, NULL, &target, request.rotationDegrees, &pivot, SDL_FLIP_NONE);
	}
}

void Renderer::RenderGameToScreen()
{
	SDL_RenderPresent(m_GameRenderer);
}

void Renderer::RenderGameToBmp()
{
	static bool initialized = false;
	static SDL_Surface* frameSurface = nullptr;

	if (!initialized)
	{
		frameSurface = SDL_CreateRGBSurfaceWithFormat(0, m_GameWindowSize.x, m_GameWindowSize.y, 24, SDL_PIXELFORMAT_RGB24);
		initialized = true;
	}

	if (SDL_RenderReadPixels(m_GameRenderer, NULL, SDL_PIXELFORMAT_RGB24, frameSurface->pixels, frameSurface->pitch) != 0)
		SDL_Log("SDL_RenderReadPixels() failed: %s", SDL_GetError());

	std::string outputPath = "frame.bmp";

	if (SDL_SaveBMP(frameSurface, outputPath.c_str()) != 0)
		SDL_Log("SDL_SaveBMP() failed: %s", SDL_GetError());
}
