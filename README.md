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
```
<img width="954" height="747" alt="image" src="https://github.com/user-attachments/assets/321ff8ff-4c78-4ead-9742-738007171710" />
