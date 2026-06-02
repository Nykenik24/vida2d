#include "vida/Engine.hpp"
#include "vida/Event.hpp"
#include <chrono>

namespace Vida {
bool Engine::Update() {
  auto now = std::chrono::high_resolution_clock::now();
  dt = std::chrono::duration<float>(now - prev).count();
  prev = now;

  game->Handle(EventType::LoopEnter);
  if (!game->Loop(dt)) {
    Quit();
    return false;
  }
  game->Handle(EventType::LoopExit);

  if (!renderer.ShouldClose()) {
    game->Handle(EventType::DrawEnter);
    renderer.BeginFrame();
    if (!game->Draw(&renderer)) {
      Quit();
      return false;
    }
    renderer.EndFrame();
    game->Handle(EventType::DrawExit);
  } else {
    Quit();
  }

  return true;
}

void Engine::Quit() { running = false; }
} // namespace Vida
