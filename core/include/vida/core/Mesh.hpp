#pragma once

#include "vida/core/Math.hpp"
#include <string>
#include <vector>

namespace Vida {

struct Vertex {
  Vec3 position;
  Vec2 uv;
  Vec3 normal;
};

struct Mesh {
  std::vector<Vertex> vertices;

  static Mesh Quad();
  static Mesh Disc(int segments = 32);
  static Mesh Triangle();
  static Mesh Cube();
  static Mesh Sphere(int rings = 16, int sectors = 16);
  static Mesh Cone(int segments = 32);
  static Mesh Pyramid();
  static Mesh FromOBJ(const std::string &path);
};

} // namespace Vida
