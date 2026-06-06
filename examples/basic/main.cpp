#include "vida/core/Color.hpp"
#include "vida/renderer3d/Renderer3D.hpp"
#include "vida/window/Window.hpp"

int main() {
  Vida::Window window(800, 600, "Vida 2D");
  Vida::Renderer3D renderer(window);

  renderer.GetCamera().Move({2, 0, 5});
  renderer.GetCamera().Point({1, 0, 0});

  while (!window.ShouldClose()) {
    window.PollEvents();
    renderer.Clear(Vida::ColorRGBA::Black);
    renderer.DrawCube({0, 0, 0}, {1, 1, 1}, Vida::ColorRGBA::Blue);
    renderer.Present();
  }
}
