#include "vida2d.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"

namespace Vida2D {
Context *Context::instance = nullptr;
std::mutex Context::mtx;

bool ClearScreen() {
  auto &ctx = Context::GetInstance();
  auto color = ctx.GetClearColor();
  SDL_SetRenderDrawColor(ctx.GetRenderer(), color.r, color.g, color.b, color.a);
  return SDL_RenderClear(ctx.GetRenderer());
}

void PollEvents() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_EVENT_QUIT)
      Context::GetInstance().SetRunning(false);
  }
}
} // namespace Vida2D
