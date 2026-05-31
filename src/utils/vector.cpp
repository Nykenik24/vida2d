#include "vida2d/vec.hpp"

namespace Vida2D {
Vector2 Vector2::Translated(float x, float y) {
  return Vector2(this->x + x, this->y + y);
}

Vector2 Vector2::TranslatedX(float diff) {
  return Vector2(this->x + diff, this->y);
}

Vector2 Vector2::TranslatedY(float diff) {
  return Vector2(this->x, this->y + diff);
}
} // namespace Vida2D
