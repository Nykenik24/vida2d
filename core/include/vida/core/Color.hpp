#pragma once

#include "vida/core/Math.hpp"

namespace Vida {
class ColorRGBA {
public:
  ColorRGBA(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {};
  ColorRGBA(int r, int g, int b) : r(r), g(g), b(b), a(255) {};

  ColorRGBA(Vec3 rgb) : r(rgb.x), g(rgb.y), b(rgb.z), a(255) {};
  ColorRGBA(Vec3 rgb, int a) : r(rgb.x), g(rgb.y), b(rgb.z), a(a) {};

  ColorRGBA() : r(255), g(255), b(255), a(255) {};

  ColorRGBA(ColorRGBA &&) = default;
  ColorRGBA(const ColorRGBA &) = default;
  ColorRGBA &operator=(ColorRGBA &&) = default;
  ColorRGBA &operator=(const ColorRGBA &) = default;
  ~ColorRGBA() = default;

  int r, g, b, a;

  static ColorRGBA Transparent;
  static ColorRGBA White;
  static ColorRGBA Black;
  static ColorRGBA Red;
  static ColorRGBA Green;
  static ColorRGBA Blue;
};

} // namespace Vida
