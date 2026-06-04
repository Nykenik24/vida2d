// clang-format off
#include <GL/glew.h>
// clang-format on
#include "vida/render/Renderer.hpp"
#include "vida/Color.hpp"
#include "vida/Vector.hpp"
#include "vida/render/Triangulate.hpp"
#include <GL/gl.h>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

namespace Vida {
Renderer::Renderer(std::string title, Vector2f size) : window_size(size) {
  static bool initialized = false;
  if (!initialized) {
    int argc = 0;
    glutInit(&argc, nullptr);
    initialized = true;
  }
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(static_cast<int>(size.x), static_cast<int>(size.y));
  windowId = glutCreateWindow(title.c_str());

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glutDisplayFunc([] {});
  glutCloseFunc([] { Renderer::shouldClose = true; });

  GLenum res = glewInit();
  if (res != GLEW_OK) {
    fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
    exit(1);
  }

  InitShaders();
}

Renderer::~Renderer() {
  glDeleteProgram(shaderProgram);
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  if (windowId != 0)
    glutDestroyWindow(windowId);
}

void Renderer::DrawDots(std::vector<Vector2f> dots, ColorRGBA color,
                        float size) {
  for (const auto &dot : dots) {
    auto [nx, ny] = PixelToNDC(dot);
    glPointSize(size);
    DrawPrimitive(GL_POINTS, {nx, ny}, color);
  }
}

void Renderer::DrawLine(Vector2f a, Vector2f b, ColorRGBA color, float width) {
  auto [ax, ay] = PixelToNDC(a);
  auto [bx, by] = PixelToNDC(b);
  glLineWidth(width);
  DrawPrimitive(GL_LINES, {ax, ay, bx, by}, color);
}

void Renderer::DrawTriangle(Vector2f a, Vector2f b, Vector2f c,
                            ColorRGBA color) {
  auto [ax, ay] = PixelToNDC(a);
  auto [bx, by] = PixelToNDC(b);
  auto [cx, cy] = PixelToNDC(c);
  DrawPrimitive(GL_TRIANGLES, {ax, ay, bx, by, cx, cy}, color);
}

void Renderer::DrawFillTriangle(Vector2f a, Vector2f b, Vector2f c,
                                ColorRGBA color) {
  auto [ax, ay] = PixelToNDC(a);
  auto [bx, by] = PixelToNDC(b);
  auto [cx, cy] = PixelToNDC(c);
  DrawPrimitive(GL_TRIANGLE_FAN, {ax, ay, bx, by, cx, cy}, color);
}

void Renderer::DrawPolygon(const std::vector<Vector2f> &points,
                           ColorRGBA color) {
  std::vector<float> verts;
  verts.reserve(points.size() * 2);
  for (auto &p : points) {
    auto [nx, ny] = PixelToNDC(p);
    verts.push_back(nx);
    verts.push_back(ny);
  }
  DrawPrimitive(GL_LINE_LOOP, verts, color);
}

void Renderer::DrawFillPolygon(const std::vector<Vector2f> &points,
                               ColorRGBA color) {
  auto triangles = Triangulate(points);
  if (triangles.empty())
    return;

  std::vector<float> verts;
  verts.reserve(triangles.size() * 6);

  for (const Vector3 &tri : triangles) {
    for (int idx : {(int)tri.x, (int)tri.y, (int)tri.z}) {
      auto [nx, ny] = PixelToNDC(points[idx]);
      verts.push_back(nx);
      verts.push_back(ny);
    }
  }

  DrawPrimitive(GL_TRIANGLES, verts, color);
}

std::vector<Vector2f> RectanglePoints(Vector2f pos, Vector2f size) {
  return {pos,
          {pos.x + size.x, pos.y},
          {pos.x + size.x, pos.y + size.y},
          {pos.x, pos.y + size.y}};
}

void Renderer::DrawRect(Vector2f pos, Vector2f size, ColorRGBA color) {
  DrawPolygon(RectanglePoints(pos, size), color);
}

void Renderer::DrawFillRect(Vector2f pos, Vector2f size, ColorRGBA color) {
  DrawFillPolygon(RectanglePoints(pos, size), color);
}

std::vector<Vector2f> CirclePoints(Vector2f center, float radius,
                                   int segments) {
  std::vector<Vector2f> points;
  points.reserve(segments);
  for (int i = 0; i < segments; i++) {
    float angle = (2.0f * M_PI * i) / segments;
    points.push_back(
        {center.x + radius * cosf(angle), center.y + radius * sinf(angle)});
  }
  return points;
}

void Renderer::DrawCircle(Vector2f center, float radius, ColorRGBA color,
                          int segments) {
  DrawPolygon(CirclePoints(center, radius, segments), color);
}

void Renderer::DrawFillCircle(Vector2f center, float radius, ColorRGBA color,
                              int segments) {
  DrawFillPolygon(CirclePoints(center, radius, segments), color);
}

} // namespace Vida
