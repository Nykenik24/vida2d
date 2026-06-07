#pragma once

#include "vida/core/Math.hpp"

namespace Vida {
class ColorRGBA {
public:
  ColorRGBA(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {};
  ColorRGBA(float r, float g, float b) : r(r), g(g), b(b), a(255) {};

  ColorRGBA(Vec3 rgb) : r(rgb.x), g(rgb.y), b(rgb.z), a(255) {};
  ColorRGBA(Vec3 rgb, float a) : r(rgb.x), g(rgb.y), b(rgb.z), a(a) {};

  ColorRGBA() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {};

  ColorRGBA(ColorRGBA &&) = default;
  ColorRGBA(const ColorRGBA &) = default;
  ColorRGBA &operator=(ColorRGBA &&) = default;
  ColorRGBA &operator=(const ColorRGBA &) = default;
  ~ColorRGBA() = default;

  Vec3 ToVec3() const;
  Vec4 ToVec4() const;

  float r, g, b, a;

  static const ColorRGBA Transparent;
  static const ColorRGBA White;
  static const ColorRGBA Black;
  static const ColorRGBA Red;
  static const ColorRGBA Green;
  static const ColorRGBA Blue;
  static const ColorRGBA Yellow;
  static const ColorRGBA Cyan;
};

} // namespace Vida
