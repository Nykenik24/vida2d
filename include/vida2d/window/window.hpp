#pragma once

#include "vida2d/int_types.hpp"
#include "vida2d/vec.hpp"
#include <string>
namespace Vida2D {
namespace Window {
bool SetTitle(const std::string title);
bool SetSize(Vector2 size);
bool SetWidth(uint32 width);
bool SetHeight(uint32 height);

std::string GetTitle();
Vector2 GetSize();
uint32 GetWidth();
uint32 GetHeight();
} // namespace Window
} // namespace Vida2D
