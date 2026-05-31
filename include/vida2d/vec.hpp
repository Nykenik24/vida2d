#pragma once

namespace Vida2D {
class Vector2 {
public:
  Vector2(float x, float y);
  Vector2(Vector2 &&) = default;
  Vector2(const Vector2 &) = default;

  Vector2 &operator=(Vector2 &&) = default;
  Vector2 &operator=(const Vector2 &) = default;
  Vector2 &operator+=(const Vector2 &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  Vector2 &operator-=(const Vector2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
  Vector2 &operator*=(const Vector2 &other) {
    x *= other.x;
    y *= other.y;
    return *this;
  }
  Vector2 &operator/=(const Vector2 &other) {
    x /= other.x;
    y /= other.y;
    return *this;
  }
  Vector2 operator+(const Vector2 &other) const {
    return Vector2(x + other.x, y + other.y);
  }
  Vector2 operator-(const Vector2 &other) const {
    return Vector2(x - other.x, y - other.y);
  }
  Vector2 operator*(const Vector2 &other) const {
    return Vector2(x * other.x, y * other.y);
  }
  Vector2 operator/(const Vector2 &other) const {
    return Vector2(x / other.x, y / other.y);
  }

  ~Vector2() = default;

  float x, y;

  // Returns a new translated version of the vector.
  //
  // Doesn't mutate the original vector.
  Vector2 Translated(float x, float y);
  // Returns a new X-translated version of the vector.
  //
  // Doesn't mutate the original vector.
  Vector2 TranslatedX(float diff);
  // Returns a new Y-translated version of the vector.
  //
  // Doesn't mutate the original vector.
  Vector2 TranslatedY(float diff);

private:
};

inline Vector2::Vector2(float x, float y) : x(x), y(y) {}
} // namespace Vida2D
