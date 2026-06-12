#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "imgui.h"
#include "vida/engine/Engine.hpp"
#include "vida/engine/EventBus.hpp"
#include "vida/logger.h"
#include <cstdio>

int main(void) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return 1;
  }

  vida_set_minlog(VIDA_LOG_INFO);

  Vida::Engine engine;

  Vida::Event::EventBus bus;
  auto sub = Vida::Event::Subscriber::make(bus);
  Vida::Event::Publisher pub(bus, "ButtonClicker");

  sub->Sub("ButtonClicker");
  sub->On("ClickButton", [] {
    printf("Button Clicked!\n");
    return true;
  });

  while (engine.Running()) {
    engine.PollEvents();

    engine.BeginFrame();

    ImGui::Begin("Vida Engine");

    ImGui::Text("Hello world");
    ImGui::Separator();

    static float value = 0.5f;
    ImGui::SliderFloat("Value", &value, 0.0f, 1.0f);

    if (ImGui::Button("Click me")) {
      pub.Emit("ClickButton");
    }

    ImGui::End();

    engine.EndFrame();
  }

  engine.Quit();
  return 0;
}
