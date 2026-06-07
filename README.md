# vida

LÖVE-inspired game framework made in C++, for C++.

**REALLY W.I.P., don't expect much.**

## Usage

### Building from source

First, build the library:
```bash
cmake -B build && cmake --build build
```

Then, use the generated libraries in `lib/`, or try out the examples at `bin/`.

### Example

```cpp
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

    renderer.DrawCube({-3.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f},
                      Vida::ColorRGBA::Blue, Vida::FX::Lit);

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
```

<img width="1168" height="555" alt="image" src="https://github.com/user-attachments/assets/1a32bba0-154c-4cd9-8b63-f0d1c91be21e" />
