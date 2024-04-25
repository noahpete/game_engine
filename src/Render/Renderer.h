#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "Configurator.h"
#include "Render/Gui.h"
#include "Scene/Scene.h"
#include "Application.h"

class Application;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void LoadTextures(); 
	void Update();
	void StartFrame();
	void RenderFrame();
	void CleanupFrame();

	void RenderGui();
	void RenderScene();
	void RenderActor(Actor* actor);

	void RenderGameToScreen();
	void RenderGameToBmp();

	static SDL_Window* GetGameWindow() { return m_GameWindow; }

private:
	glm::ivec2 m_EditorWindowSize = { 1600, 900 };
	glm::ivec3 m_EditorClearColor = { 255, 255, 255 };
	static SDL_Window* m_EditorWindow;
	static SDL_Renderer* m_EditorRenderer;

	glm::ivec2 m_GameWindowSize = { 640, 360 };
	glm::ivec3 m_GameClearColor = { 255, 255, 255 };
	static SDL_Window* m_GameWindow;
	static SDL_Renderer* m_GameRenderer;

	static std::unordered_map<std::string, SDL_Texture*> m_Textures;

};
