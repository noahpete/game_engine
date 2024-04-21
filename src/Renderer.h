#pragma once

#include "glm/glm.hpp"
#include "SDL2/SDL.h"
#include "Gui.h"
#include "Configurator.h"

class Renderer
{
public:
	Renderer()
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
		m_GameWindow = SDL_CreateWindow("", 0, 0, m_GameWindowSize.x, m_GameWindowSize.y, SDL_WINDOW_HIDDEN);
		m_Renderer = SDL_CreateRenderer(m_EditorWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplSDL2_InitForSDLRenderer(m_EditorWindow, m_Renderer);
		ImGui_ImplSDLRenderer2_Init(m_Renderer);
	}
	~Renderer() {}

	void Update();
	void StartFrame();
	void RenderFrame();
	void CleanupFrame();

	void RenderGui();
	void RenderScene();

private:
	glm::ivec2 m_EditorWindowSize = { 1600, 900 };
	glm::ivec3 m_EditorClearColor = { 255, 255, 255 };
	static SDL_Window* m_EditorWindow;

	glm::ivec2 m_GameWindowSize = { 640, 360 };
	glm::ivec3 m_GameClearColor = { 255, 255, 255 };
	static SDL_Window* m_GameWindow;

	static SDL_Renderer* m_Renderer;

};
