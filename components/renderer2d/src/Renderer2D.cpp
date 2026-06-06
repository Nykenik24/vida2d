#include "vida/renderer2d/Renderer2D.hpp"
#include "vida/core/Color.hpp"
#include "vida/core/Mesh.hpp"
#include "vida/renderer3d/Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Vida {

Renderer2D::Renderer2D(Window &window) : renderer(window) { LockCamera(); }

void Renderer2D::LockCamera() {
  Camera cam;
  cam.position = Vec3(0.0f, 0.0f, 1.0f);
  cam.target = Vec3(0.0f, 0.0f, 0.0f);
  cam.orthographic = true;
  renderer.SetCamera(cam);
}

void Renderer2D::Clear(ColorRGBA color) { renderer.Clear(color); }

void Renderer2D::Present() { renderer.Present(); }

void Renderer2D::DrawRect(Vec2 position, Vec2 size, ColorRGBA color) {
  renderer.DrawQuad(position, size, Vec3(color.r, color.g, color.b));
}

void Renderer2D::DrawCircle(Vec2 position, float radius, ColorRGBA color) {
  static const Mesh mesh = Mesh::Disc(32);

  Mat4 transform =
      glm::translate(Mat4(1.0f), Vec3(position, 0.0f)) *
      glm::scale(Mat4(1.0f), Vec3(radius * 2.0f, radius * 2.0f, 1.0f));

  renderer.DrawMesh(mesh, transform, color);
}

void Renderer2D::DrawTriangle(Vec2 position, Vec2 size, ColorRGBA color) {
  static const Mesh mesh = Mesh::Triangle();

  Mat4 transform = glm::translate(Mat4(1.0f), Vec3(position, 0.0f)) *
                   glm::scale(Mat4(1.0f), Vec3(size, 1.0f));

  renderer.DrawMesh(mesh, transform, color);
}

void Renderer2D::DrawSprite(Vec2 position, Vec2 size, const Texture &texture) {
  renderer.DrawQuad(position, size, texture);
}

void Renderer2D::DrawSprite(Vec2 position, Vec2 size, const Texture &texture,
                            ColorRGBA tint) {
  static const Mesh mesh = Mesh::Quad();
  Mat4 transform = glm::translate(Mat4(1.0f), Vec3(position, 0.0f)) *
                   glm::scale(Mat4(1.0f), Vec3(size, 1.0f));
  renderer.DrawMesh(mesh, transform, tint, &texture);
}
} // namespace Vida
