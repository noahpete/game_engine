#include "Renderer.h"

SDL_Window* Renderer::m_EditorWindow;
SDL_Window* Renderer::m_GameWindow;
SDL_Renderer* Renderer::m_Renderer;

void Renderer::Update()
{
}

void Renderer::StartFrame()
{
	SDL_SetRenderDrawColor(m_Renderer, m_EditorClearColor.r, m_EditorClearColor.g, m_EditorClearColor.b, 255);
	SDL_RenderClear(m_Renderer);
}

void Renderer::RenderFrame()
{
	RenderScene();
	RenderGui();

	SDL_RenderPresent(m_Renderer);
}

void Renderer::CleanupFrame()
{
}

void Renderer::RenderGui()
{
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();
	Gui::ShowViewport();
	Gui::ShowActors();
	Gui::ShowProperties();

	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::RenderScene()
{
}
