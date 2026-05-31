#pragma once

#include "vida2d/int_types.hpp"
namespace Vida2D {
class Color {
public:
  Color(uint8 r, uint8 g, uint8 b, uint8 a);
  Color();
  Color(Color &&) = default;
  Color(const Color &) = default;
  Color &operator=(Color &&) = default;
  Color &operator=(const Color &) = default;
  ~Color() = default;

  uint8 r, g, b, a;

private:
};

inline Color::Color() : r(0), g(0), b(0), a(255) {}
inline Color::Color(uint8 r, uint8 g, uint8 b, uint8 a)
    : r(r), g(g), b(b), a(a) {}

inline const Color White(255, 255, 255, 255);
inline const Color Black(0, 0, 0, 255);
inline const Color Red(255, 0, 0, 255);
inline const Color Green(0, 255, 0, 255);
inline const Color Blue(0, 0, 255, 255);
} // namespace Vida2D
