#include "vida/engine/engine.h"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL_log.h>
#include <stdlib.h>

engine_t *new_engine() {
  engine_t *eng = malloc(sizeof(engine_t));

  eng->window = SDL_CreateWindow(VIDA_WINDOW_TITLE, VIDA_WINDOW_START_WIDTH,
                                 VIDA_WINDOW_START_HEIGHT, 0);

  if (!eng->window) {
    SDL_Log("Window creation failed: %s", SDL_GetError());
    return NULL;
  }

  eng->renderer = SDL_CreateRenderer(eng->window, NULL);

  if (!eng->renderer) {
    SDL_Log("Renderer creation failed: %s", SDL_GetError());
    SDL_DestroyWindow(eng->window);
    free(eng);
    return NULL;
  }

  return eng;
}

void destroy_engine(engine_t *eng) {
  if (!eng)
    return;

  if (eng->window)
    SDL_DestroyWindow(eng->window);

  if (eng->renderer)
    SDL_DestroyRenderer(eng->renderer);

  free(eng);
}
