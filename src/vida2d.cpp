#include "vida2d.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_timer.h"
#include "vida2d/int_types.hpp"

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

bool Update() {
  uint64 now = SDL_GetTicksNS();
  auto &ctx = Context::GetInstance();
  uint64 last = ctx.GetLastTime();
  float dt = last == 0 ? 0.0f : (now - last) / 1e9f;
  ctx.SetDT(dt);
  ctx.SetLastTime(now);
  return true;
}
} // namespace Vida2D
