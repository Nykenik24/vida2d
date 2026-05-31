#pragma once

#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "vida2d/color.hpp"
#include <mutex>
#include <stdexcept>
#include <string>

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

private:
  Context(std::string window_title, unsigned width, unsigned height);

  static Context *instance;
  static std::mutex mtx;

  SDL_Window *window;
  SDL_Renderer *renderer;
  bool running;

  Color clear_color = Black;
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
}

inline Context::~Context() { Quit(); }

inline void Context::Quit() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

inline Color Context::GetClearColor() const { return clear_color; }
inline void Context::SetClearColor(Color color) { clear_color = color; }

inline int Context::IsRunning() const { return running; }
inline void Context::SetRunning(bool running) { this->running = running; }
inline SDL_Renderer *Context::GetRenderer() const { return renderer; }
inline SDL_Window *Context::GetWindow() const { return window; }

bool Update();
bool ClearScreen();
void PollEvents();

inline bool Running() { return Context::GetInstance().IsRunning(); }
} // namespace Vida2D
