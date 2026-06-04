#include "vida/Engine.hpp"
#include "vida/Event.hpp"
#include <chrono>

namespace Vida {
bool Engine::Update() {
  if (game->WantToQuit()) {
    Quit();
    return true;
  }

  auto now = std::chrono::high_resolution_clock::now();
  dt = std::chrono::duration<float>(now - prev).count();
  prev = now;
  game->dt = dt;

  if (first_loop) {
    first_loop = false;
    game->Handle(Event(EventType::LoopFirstEnter));
  }
  game->Handle(Event(EventType::LoopEnter));
  if (!game->Loop()) {
    Quit();
    return false;
  }
  game->Handle(Event(EventType::LoopExit));

  if (first_draw) {
    first_draw = false;
    game->Handle(Event(EventType::DrawFirstEnter, &renderer));
  }
  if (!renderer.ShouldClose()) {
    game->Handle(Event(EventType::DrawEnter, &renderer));
    renderer.BeginFrame();
    if (!game->Draw(&renderer)) {
      Quit();
      return false;
    }
    renderer.EndFrame();
    game->Handle(Event(EventType::DrawExit, &renderer));
  } else {
    Quit();
  }

  return true;
}

void Engine::Quit() { running = false; }

int Engine::Run() {
  while (Running()) {
    if (!Update()) {
      return 1;
    }
  }
  return 0;
}

void Engine::SetWindowTitle(std::string title) {
  glutSetWindowTitle(title.c_str());
}

void Engine::SetWindowSize(Vector2f size) { glutReshapeWindow(size.x, size.y); }
void Engine::SetWindowPos(Vector2f pos) { glutPositionWindow(pos.x, pos.y); }
} // namespace Vida
