#ifndef INCLUDE_ENGINE_ENGINE_H_
#define INCLUDE_ENGINE_ENGINE_H_

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#define VIDA_WINDOW_TITLE "Vida Engine"
#define VIDA_RENDERER_TITLE "Vida Renderer"
#define VIDA_WINDOW_START_WIDTH 1080
#define VIDA_WINDOW_START_HEIGHT 720

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} engine_t;

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

engine_t *new_engine(void);
void destroy_engine(engine_t *eng);

#ifdef __cplusplus
}
#endif

#endif // !INCLUDE_ENGINE_ENGINE_H_
