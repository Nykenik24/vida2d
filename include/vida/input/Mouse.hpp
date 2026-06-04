#pragma once

#include "GL/freeglut_std.h"
#include <optional>
namespace Vida {
enum class MouseBttn {
  None,
  Left,
  Right,
  Middle,
  ScrollUp,
  ScrollDown,
};

inline std::optional<MouseBttn> MouseButtonFromGlut(int m) {
  switch (m) {
  case GLUT_LEFT_BUTTON:
    return MouseBttn::Left;
  case GLUT_MIDDLE_BUTTON:
    return MouseBttn::Middle;
  case GLUT_RIGHT_BUTTON:
    return MouseBttn::Right;
  case 3:
    return MouseBttn::ScrollUp;
  case 4:
    return MouseBttn::ScrollDown;
  }
  return std::nullopt;
}
} // namespace Vida
