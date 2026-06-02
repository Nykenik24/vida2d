#pragma once

class Vector2 {
public:
  Vector2(float x, float y) : x(x), y(y) {};
  Vector2(Vector2 &&) = default;
  Vector2(const Vector2 &) = default;
  Vector2 &operator=(Vector2 &&) = default;
  Vector2 &operator=(const Vector2 &) = default;
  ~Vector2() = default;

  float x, y;
};

class Vector3 {
public:
  Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
  Vector3(Vector3 &&) = default;
  Vector3(const Vector3 &) = default;
  Vector3 &operator=(Vector3 &&) = default;
  Vector3 &operator=(const Vector3 &) = default;
  ~Vector3() = default;

  float x, y, z;
};
