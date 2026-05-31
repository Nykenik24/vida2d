#pragma once

#include "vida2d/color.hpp"
#include "vida2d/vec.hpp"
namespace Vida2D {
namespace Render {

bool Point(Vector2 pos);
bool Line(Vector2 start, Vector2 end);

bool Rect(Vector2 pos, Vector2 size);
bool RectFill(Vector2 pos, Vector2 size);

bool Triangle(Vector2 p1, Vector2 p2, Vector2 p3);
bool TriangleFill(Vector2 p1, Vector2 p2, Vector2 p3);

bool Circle(Vector2 center, float radius);
bool CircleFill(Vector2 center, float radius);

bool SetColor(Color color);
void SetBackgroundColor(Color color);
} // namespace Render
} // namespace Vida2D
