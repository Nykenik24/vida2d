#pragma once

#include "vida/core/Color.hpp"
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include "vida/core/Math.hpp"
#include "vida/renderer3d/Camera.hpp"
#include "vida/window/Window.hpp"

namespace Vida {

class Renderer3D {
public:
  explicit Renderer3D(Window &window);
  ~Renderer3D();

  Renderer3D(const Renderer3D &) = delete;
  Renderer3D &operator=(const Renderer3D &) = delete;

  void Clear(ColorRGBA color);
  void Present();

  void SetCamera(const Camera &camera);
  Camera &GetCamera() { return camera; }

  void DrawMesh(const Vec3 *vertices, size_t count, const Mat4 &transform,
                ColorRGBA color);
  void DrawQuad(Vec2 position, Vec2 size, ColorRGBA color);
  void DrawCube(Vec3 position, Vec3 size, ColorRGBA color);

  Window &GetWindow() { return window; }

private:
  Window &window;
  Camera camera;

  GLuint shader_program;
  GLuint VAO, VBO;

  void InitShaders();
  void InitBuffers();
};

} // namespace Vida
