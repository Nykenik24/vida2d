#include "vida/core/Color.hpp"

namespace Vida {
ColorRGBA ColorRGBA::Transparent(0, 0, 0, 0);
ColorRGBA ColorRGBA::White(255, 255, 255);
ColorRGBA ColorRGBA::Black(0, 0, 0);
ColorRGBA ColorRGBA::Red(255, 0, 0);
ColorRGBA ColorRGBA::Green(0, 255, 0);
ColorRGBA ColorRGBA::Blue(0, 0, 255);
const ColorRGBA ColorRGBA::Yellow = {1.0f, 1.0f, 0.0f, 1.0f};
const ColorRGBA ColorRGBA::Cyan = {0.0f, 1.0f, 1.0f, 1.0f};
} // namespace Vida
