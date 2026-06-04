#pragma once

#include "vida/Color.hpp"
#include "vida/Vector.hpp"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <string>
#include <vector>

namespace Vida {

class Renderer {
public:
  Renderer(std::string title, Vector2f size);
  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;
  Renderer(Renderer &&) = default;
  Renderer &operator=(Renderer &&) = default;
  ~Renderer();

  void DrawDots(std::vector<Vector2f> dots, ColorRGBA color = {},
                float size = 1.0f);
  void DrawLine(Vector2f a, Vector2f b, ColorRGBA color = {},
                float width = 1.0f);

  void DrawTriangle(Vector2f a, Vector2f b, Vector2f c, ColorRGBA color = {});
  void DrawFillTriangle(Vector2f a, Vector2f b, Vector2f c,
                        ColorRGBA color = {});

  void DrawPolygon(const std::vector<Vector2f> &points, ColorRGBA color = {});
  void DrawFillPolygon(const std::vector<Vector2f> &points,
                       ColorRGBA color = {});

  void DrawRect(Vector2f pos, Vector2f size, ColorRGBA color = {});
  void DrawFillRect(Vector2f pos, Vector2f size, ColorRGBA color = {});

  void DrawCircle(Vector2f center, float radius, ColorRGBA color = {},
                  int segments = 64);
  void DrawFillCircle(Vector2f center, float radius, ColorRGBA color = {},
                      int segments = 64);

private:
  void InitShaders();
  Vector2f PixelToNDC(Vector2f pixel) const;
  void DrawPrimitive(GLenum mode, const std::vector<float> &verts,
                     ColorRGBA color);

  int windowId = 0;
  GLuint shaderProgram = 0;
  GLint colorUniformLoc = -1;
  GLuint vao = 0;
  GLuint vbo = 0;
  size_t vboCapacity = 0;
  Vector2f windowSize;

  static inline bool shouldClose = false;

  void BeginFrame();
  void EndFrame();
  bool ShouldClose() const { return shouldClose; }

  friend class Engine;
};

} // namespace Vida
