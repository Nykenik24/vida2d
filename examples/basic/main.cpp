#include "vida/core/Color.hpp"
#include "vida/renderer3d/FX.hpp"
#include "vida/renderer3d/Renderer3D.hpp"
#include "vida/window/Window.hpp"

int main() {
  Vida::Window window(1200, 600, "Vida FX Demo");
  Vida::Renderer3D renderer(window);

  renderer.GetCamera().Move({0.0f, 2.0f, 8.0f});
  renderer.GetCamera().Point({0.0f, 0.0f, 0.0f});

  float dt = 0.016f;

  while (!window.ShouldClose()) {
    window.PollEvents();
    renderer.Update(dt);

    renderer.Clear(Vida::ColorRGBA(0.1f, 0.1f, 0.1f, 1.0f));

    renderer.DrawCube({-5.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f},
                      Vida::ColorRGBA::Red, Vida::FX::Unlit);

    Vida::FXParams lit_params;
    lit_params.ambient = 0.25f;
    renderer.DrawCube({-3.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f},
                      Vida::ColorRGBA::Blue, Vida::FX::Lit, lit_params);

    renderer.DrawCube({-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f},
                      Vida::ColorRGBA::Green, Vida::FX::Outline);

    renderer.DrawCube({1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f},
                      Vida::ColorRGBA(1.0f, 1.0f, 1.0f, 0.5f),
                      Vida::FX::Transparent);

    renderer.DrawCube({3.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f},
                      Vida::ColorRGBA::Yellow, Vida::FX::Pulse);

    renderer.DrawCube({5.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f},
                      Vida::ColorRGBA::Cyan, Vida::FX::Dissolve);

    renderer.Present();
  }
}
