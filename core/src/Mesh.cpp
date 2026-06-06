#include "vida/core/Mesh.hpp"
#include "vida/core/OBJLoader.hpp"

namespace Vida {
Mesh Mesh::Cube() {
  Mesh m;

  auto face = [&](Vec3 a, Vec3 b, Vec3 c, Vec3 d, Vec3 n) {
    m.vertices.push_back({a, {0.0f, 0.0f}, n});
    m.vertices.push_back({b, {1.0f, 0.0f}, n});
    m.vertices.push_back({c, {1.0f, 1.0f}, n});
    m.vertices.push_back({c, {1.0f, 1.0f}, n});
    m.vertices.push_back({d, {0.0f, 1.0f}, n});
    m.vertices.push_back({a, {0.0f, 0.0f}, n});
  };

  face({-0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, 0.5f}, {0.5f, 0.5f, 0.5f},
       {-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f});
  face({0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f},
       {0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f});
  face({-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f},
       {-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f});
  face({0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, 0.5f, -0.5f},
       {0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f});
  face({-0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, -0.5f},
       {-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f});
  face({-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, 0.5f},
       {-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f});

  return m;
}

Mesh Mesh::Quad() {
  Mesh m;
  m.vertices = {
      {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
      {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
      {{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
      {{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
      {{-0.5f, 0.5f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
      {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
  };
  return m;
}

Mesh Mesh::Sphere(int rings, int sectors) {
  Mesh m;

  for (int r = 0; r < rings; r++) {
    for (int s = 0; s < sectors; s++) {
      float y0 = sin(-M_PI_2 + M_PI * r / rings);
      float y1 = sin(-M_PI_2 + M_PI * (r + 1) / rings);
      float r0 = cos(M_PI * r / rings);
      float r1 = cos(M_PI * (r + 1) / rings);

      float a0 = 2.0f * M_PI * s / sectors;
      float a1 = 2.0f * M_PI * (s + 1) / sectors;

      Vec3 p0 = {r0 * cos(a0), y0, r0 * sin(a0)};
      Vec3 p1 = {r1 * cos(a0), y1, r1 * sin(a0)};
      Vec3 p2 = {r1 * cos(a1), y1, r1 * sin(a1)};
      Vec3 p3 = {r0 * cos(a1), y0, r0 * sin(a1)};

      Vec2 uv0 = {(float)s / sectors, (float)r / rings};
      Vec2 uv1 = {(float)s / sectors, (float)(r + 1) / rings};
      Vec2 uv2 = {(float)(s + 1) / sectors, (float)(r + 1) / rings};
      Vec2 uv3 = {(float)(s + 1) / sectors, (float)r / rings};

      m.vertices.push_back({p0 * 0.5f, uv0, p0});
      m.vertices.push_back({p1 * 0.5f, uv1, p1});
      m.vertices.push_back({p2 * 0.5f, uv2, p2});

      m.vertices.push_back({p2 * 0.5f, uv2, p2});
      m.vertices.push_back({p3 * 0.5f, uv3, p3});
      m.vertices.push_back({p0 * 0.5f, uv0, p0});
    }
  }
  return m;
}

Mesh Mesh::Disc(int segments) {
  Mesh m;
  Vec3 normal = {0.0f, 0.0f, 1.0f};

  for (int i = 0; i < segments; i++) {
    float a0 = 2.0f * M_PI * i / segments;
    float a1 = 2.0f * M_PI * (i + 1) / segments;

    float x0 = cos(a0) * 0.5f, y0 = sin(a0) * 0.5f;
    float x1 = cos(a1) * 0.5f, y1 = sin(a1) * 0.5f;

    m.vertices.push_back({{0.0f, 0.0f, 0.0f}, {0.5f, 0.5f}, normal});
    m.vertices.push_back({{x0, y0, 0.0f}, {x0 + 0.5f, y0 + 0.5f}, normal});
    m.vertices.push_back({{x1, y1, 0.0f}, {x1 + 0.5f, y1 + 0.5f}, normal});
  }
  return m;
}

Mesh Mesh::Cone(int segments) {
  Mesh m;

  for (int i = 0; i < segments; i++) {
    float a0 = 2.0f * M_PI * i / segments;
    float a1 = 2.0f * M_PI * (i + 1) / segments;

    float x0 = cos(a0) * 0.5f, z0 = sin(a0) * 0.5f;
    float x1 = cos(a1) * 0.5f, z1 = sin(a1) * 0.5f;

    Vec3 n0 = glm::normalize(Vec3(cos(a0), 0.5f, sin(a0)));
    Vec3 n1 = glm::normalize(Vec3(cos(a1), 0.5f, sin(a1)));
    Vec3 ns = glm::normalize(n0 + n1);

    float u0 = (float)i / segments;
    float u1 = (float)(i + 1) / segments;

    m.vertices.push_back({{0.0f, 0.5f, 0.0f}, {(u0 + u1) * 0.5f, 1.0f}, ns});
    m.vertices.push_back({{x0, -0.5f, z0}, {u0, 0.0f}, n0});
    m.vertices.push_back({{x1, -0.5f, z1}, {u1, 0.0f}, n1});

    Vec3 down = {0.0f, -1.0f, 0.0f};
    m.vertices.push_back({{0.0f, -0.5f, 0.0f}, {0.5f, 0.5f}, down});
    m.vertices.push_back({{x1, -0.5f, z1}, {x1 + 0.5f, z1 + 0.5f}, down});
    m.vertices.push_back({{x0, -0.5f, z0}, {x0 + 0.5f, z0 + 0.5f}, down});
  }

  return m;
}

Mesh Mesh::Pyramid() {
  Mesh m;

  Vec3 tl = {-0.5f, -0.5f, 0.5f};
  Vec3 tr = {0.5f, -0.5f, 0.5f};
  Vec3 br = {0.5f, -0.5f, -0.5f};
  Vec3 bl = {-0.5f, -0.5f, -0.5f};
  Vec3 tip = {0.0f, 0.5f, 0.0f};

  Vec3 nf = glm::normalize(Vec3(0.0f, 0.5f, 1.0f));
  Vec3 nb = glm::normalize(Vec3(0.0f, 0.5f, -1.0f));
  Vec3 nr = glm::normalize(Vec3(1.0f, 0.5f, 0.0f));
  Vec3 nl = glm::normalize(Vec3(-1.0f, 0.5f, 0.0f));
  Vec3 nd = {0.0f, -1.0f, 0.0f};

  m.vertices.push_back({tip, {0.5f, 1.0f}, nf});
  m.vertices.push_back({tl, {0.0f, 0.0f}, nf});
  m.vertices.push_back({tr, {1.0f, 0.0f}, nf});

  m.vertices.push_back({tip, {0.5f, 1.0f}, nr});
  m.vertices.push_back({tr, {0.0f, 0.0f}, nr});
  m.vertices.push_back({br, {1.0f, 0.0f}, nr});

  m.vertices.push_back({tip, {0.5f, 1.0f}, nb});
  m.vertices.push_back({br, {0.0f, 0.0f}, nb});
  m.vertices.push_back({bl, {1.0f, 0.0f}, nb});

  m.vertices.push_back({tip, {0.5f, 1.0f}, nl});
  m.vertices.push_back({bl, {0.0f, 0.0f}, nl});
  m.vertices.push_back({tl, {1.0f, 0.0f}, nl});

  m.vertices.push_back({tl, {0.0f, 1.0f}, nd});
  m.vertices.push_back({tr, {1.0f, 1.0f}, nd});
  m.vertices.push_back({br, {1.0f, 0.0f}, nd});

  m.vertices.push_back({tl, {0.0f, 1.0f}, nd});
  m.vertices.push_back({br, {1.0f, 0.0f}, nd});
  m.vertices.push_back({bl, {0.0f, 0.0f}, nd});

  return m;
}
Mesh Mesh::Triangle() {
  Mesh m;
  m.vertices = {
      {{0.0f, 0.5f, 0.0f}, {0.5f, 1.0f}, {0.0f, 0.0f, 1.0f}},
      {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
      {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
  };
  return m;
}

Mesh Mesh::FromOBJ(const std::string &path) { return OBJLoader::Load(path); }
} // namespace Vida
