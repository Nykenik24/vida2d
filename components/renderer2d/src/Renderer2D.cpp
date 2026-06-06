#include "vida/renderer2d/Renderer2D.hpp"
#include "vida/core/Color.hpp"
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
} // namespace Vida
