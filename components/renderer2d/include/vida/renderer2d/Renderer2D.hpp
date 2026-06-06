#pragma once

#include "vida/core/Color.hpp"
#include "vida/core/Math.hpp"
#include "vida/renderer3d/Renderer3D.hpp"
#include "vida/texture/Texture.hpp"
#include "vida/window/Window.hpp"

namespace Vida {

class Renderer2D {
public:
  explicit Renderer2D(Window &window);

  Renderer2D(const Renderer2D &) = delete;
  Renderer2D &operator=(const Renderer2D &) = delete;

  void Clear(ColorRGBA color);
  void Present();

  void DrawRect(Vec2 position, Vec2 size, ColorRGBA color);
  void DrawCircle(Vec2 position, float radius, ColorRGBA color);
  void DrawTriangle(Vec2 position, Vec2 size, ColorRGBA color);
  void DrawSprite(Vec2 position, Vec2 size, const Texture &texture);
  void DrawSprite(Vec2 position, Vec2 size, const Texture &texture,
                  ColorRGBA tint);

private:
  Renderer3D renderer;

  void LockCamera();
};

} // namespace Vida
