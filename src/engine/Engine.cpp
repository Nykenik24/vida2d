#include "vida/engine/Engine.hpp"
#include "SDL3/SDL_init.h"
#include "backends/imgui_impl_sdlrenderer3.h"
#include "vida/engine/engine.h"

// clang-format off
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"
// clang-format on

namespace Vida {
Engine::Engine() {
  engine = new_engine();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui_ImplSDLRenderer3_Init(engine->renderer);
  ImGui_ImplSDL3_InitForSDLRenderer(engine->window, engine->renderer);

  running = true;
}

Engine::~Engine() {
  ImGui_ImplSDLRenderer3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();

  destroy_engine(engine);
}

void Engine::Update() {}
void Engine::Quit() {
  running = false;
  SDL_Quit();
}

bool Engine::PollEvents() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {

    ImGui_ImplSDL3_ProcessEvent(&event);

    if (event.type == SDL_EVENT_QUIT) {
      running = false;
    }
  }

  return true;
}

void Engine::BeginFrame() {
  SDL_SetRenderDrawColor(engine->renderer, 20, 20, 20, 255);
  SDL_RenderClear(engine->renderer);

  ImGui_ImplSDL3_NewFrame();
  ImGui_ImplSDLRenderer3_NewFrame();
  ImGui::NewFrame();
}

void Engine::EndFrame() {
  ImGui::Render();

  ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), engine->renderer);

  SDL_RenderPresent(engine->renderer);
}
} // namespace Vida
