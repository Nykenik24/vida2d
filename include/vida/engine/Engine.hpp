#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include "engine.h"

namespace Vida {
class Engine {
public:
  Engine();
  Engine(Engine &&) = default;
  Engine(const Engine &) = default;
  Engine &operator=(Engine &&) = default;
  Engine &operator=(const Engine &) = default;
  ~Engine();

  void Update();
  void Quit();
  bool Running() const { return running; };
  void ToggleRunning() { running = !running; };

  bool PollEvents();

  void BeginFrame();
  void EndFrame();

  SDL_Renderer *Renderer() const { return engine->renderer; };
  SDL_Window *Window() const { return engine->window; };

private:
  engine_t *engine;
  bool running;
};
} // namespace Vida
