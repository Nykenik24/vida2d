#include "vida2d/window/window.hpp"
#include "SDL3/SDL_video.h"
#include "vida2d.hpp"
#include "vida2d/int_types.hpp"
#include "vida2d/vec.hpp"

namespace Vida2D {
namespace Window {
bool SetTitle(const std::string title) {
  return SDL_SetWindowTitle(Context::GetInstance().window, title.c_str());
}

bool SetSize(Vector2 size) {
  return SDL_SetWindowSize(Context::GetInstance().window, size.x, size.y);
}

Vector2 GetSize() {
  int w, h;
  SDL_GetWindowSize(Context::GetInstance().window, &w, &h);
  return Vector2((uint32)w, (uint32)h);
}

bool SetWidth(uint32 width) {
  Vector2 size = GetSize();
  return SDL_SetWindowSize(Context::GetInstance().window, width, size.y);
}

bool SetHeight(uint32 height) {
  Vector2 size = GetSize();
  return SDL_SetWindowSize(Context::GetInstance().window, size.x, height);
}

std::string GetTitle() {
  return SDL_GetWindowTitle(Context::GetInstance().window);
}
uint32 GetWidth() { return GetSize().x; }
uint32 GetHeight() { return GetSize().y; }
} // namespace Window
} // namespace Vida2D
