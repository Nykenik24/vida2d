#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "vida/engine/Engine.hpp"
#include "vida/engine/ui/UI.hpp"
#include "vida/logger.h"

struct ClickButton {
  int count;
};

int main(void) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return 1;
  }

  vida_set_minlog(VIDA_LOG_INFO);

  Vida::Engine engine;

  int click_count = 0;
  while (engine.Running()) {
    engine.PollEvents();

    engine.BeginFrame();
    Vida::UI::DrawUI(false, false);
    engine.EndFrame();
  }

  engine.Quit();
  return 0;
}
