#include "vida.hpp"
#include "vida/event.hpp"
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

  game->Handle(EventType::DrawEnter);
  if (!game->Draw()) {
    Quit();
    return false;
  }
  game->Handle(EventType::DrawExit);

  return true;
}

void Engine::Quit() { running = false; }
} // namespace Vida
