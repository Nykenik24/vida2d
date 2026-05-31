#pragma once

#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "vida2d/color.hpp"
#include "vida2d/int_types.hpp"
#include <mutex>
#include <stdexcept>
#include <string>
#include <sys/types.h>

namespace Vida2D {
class Context {
public:
  Context(const Context &) = delete;
  Context(Context &&) = delete;
  Context &operator=(const Context &) = delete;
  Context &operator=(Context &&) = delete;

  ~Context();

  static Context &GetInstance();
  SDL_Renderer *GetRenderer() const;
  SDL_Window *GetWindow() const;

  static void Init(std::string window_title, unsigned width, unsigned height);

  int IsRunning() const;
  void SetRunning(bool running);

  void Quit();

  Color GetClearColor() const;
  void SetClearColor(Color color);

  TTF_Font *GetFont() const;
  void SetFont(TTF_Font *font);

  TTF_TextEngine *GetTextEngine() const;

  double GetDT() const;
  void SetDT(double dt);
  uint64 GetLastTime() const;
  void SetLastTime(uint64 last);

private:
  Context(std::string window_title, unsigned width, unsigned height);

  static Context *instance;
  static std::mutex mtx;

  SDL_Window *window;
  SDL_Renderer *renderer;
  bool running;

  Color clear_color = Black;

  TTF_Font *current_font = nullptr;
  TTF_TextEngine *text_engine;

  double dt = 0;
  uint64 time_last;
};

inline void Context::Init(std::string window_title, unsigned width,
                          unsigned height) {
  std::lock_guard<std::mutex> lock(mtx);
  if (!instance) {
    instance = new Context(std::move(window_title), width, height);
  }
}

inline Context &Context::GetInstance() {
  std::lock_guard<std::mutex> lock(mtx);
  if (!instance) {
    throw std::runtime_error("Context not initialized — call Init() first");
  }
  return *instance;
}

inline Context::Context(std::string window_title, unsigned width,
                        unsigned height)
    : running(true) {
  window = SDL_CreateWindow(window_title.c_str(), width, height, 0);
  renderer = SDL_CreateRenderer(window, NULL);
  TTF_Init();
  text_engine = TTF_CreateRendererTextEngine(renderer);
}

inline Context::~Context() { Quit(); }

inline void Context::Quit() {
  if (text_engine) {
    TTF_DestroyRendererTextEngine(text_engine);
    text_engine = nullptr;
  }
  if (renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
  }
  if (window) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }
  TTF_Quit();
  SDL_Quit();
}

inline Color Context::GetClearColor() const { return clear_color; }
inline void Context::SetClearColor(Color color) { clear_color = color; }

inline TTF_TextEngine *Context::GetTextEngine() const { return text_engine; }
inline TTF_Font *Context::GetFont() const { return current_font; }
inline void Context::SetFont(TTF_Font *font) { current_font = font; }

inline int Context::IsRunning() const { return running; }
inline void Context::SetRunning(bool running) { this->running = running; }
inline SDL_Renderer *Context::GetRenderer() const { return renderer; }
inline SDL_Window *Context::GetWindow() const { return window; }

inline double Context::GetDT() const { return dt; };
inline void Context::SetDT(double dt) { this->dt = dt; };
inline uint64 Context::GetLastTime() const { return time_last; };
inline void Context::SetLastTime(uint64 last) { time_last = last; }

bool ClearScreen();
void PollEvents();

inline bool Running() { return Context::GetInstance().IsRunning(); }

bool Update();
} // namespace Vida2D
