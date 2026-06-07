#include "vida/core/Color.hpp"
#include "vida/core/Math.hpp"

namespace Vida {
Vec3 ColorRGBA::ToVec3() const { return {r, g, b}; }
Vec4 ColorRGBA::ToVec4() const { return {r, g, b, a}; }

const ColorRGBA ColorRGBA::Transparent(0.0f, 0.0f, 0.0f, 0.0f);
const ColorRGBA ColorRGBA::White(1.0f, 1.0f, 1.0f, 1.0f);
const ColorRGBA ColorRGBA::Black(0.0f, 0.0f, 0.0f, 1.0f);
const ColorRGBA ColorRGBA::Red(1.0f, 0.0f, 0.0f, 1.0f);
const ColorRGBA ColorRGBA::Green(0.0f, 1.0f, 0.0f, 1.0f);
const ColorRGBA ColorRGBA::Blue(0.0f, 0.0f, 1.0f, 1.0f);
const ColorRGBA ColorRGBA::Yellow(1.0f, 1.0f, 0.0f, 1.0f);
const ColorRGBA ColorRGBA::Cyan(0.0f, 1.0f, 1.0f, 1.0f);
} // namespace Vida
