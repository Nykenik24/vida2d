#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "imgui.h"
#include "vida/engine/Engine.hpp"

int main(void) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return 1;
  }

  Vida::Engine engine;
  while (engine.Running()) {
    engine.PollEvents();

    engine.BeginFrame();

    ImGui::Begin("Vida Engine");

    ImGui::Text("Hello world");
    ImGui::Separator();

    static float value = 0.5f;
    ImGui::SliderFloat("Value", &value, 0.0f, 1.0f);

    if (ImGui::Button("Click me")) {
      SDL_Log("Button clicked");
    }

    ImGui::End();

    engine.EndFrame();
  }

  engine.Quit();
  return 0;
}
