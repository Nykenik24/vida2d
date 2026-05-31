# vida2d

LÖVE-based game framework made in C, for C.

**REALLY W.I.P., don't expect much.**

## Usage

### Building from source

First, build the library:
```bash
cmake -B build && cmake --build build
```

Then, use the generated library in `lib/`, or try out the examples at `bin/`.

### Example

```c
#include "vida2d.hpp"
#include "vida2d/color.hpp"
#include "vida2d/render.hpp"
#include "vida2d/vec.hpp"

int main(void) {
  Vida2D::Context::Init("test", 800, 600);

  Vida2D::Vector2 first_pos(25, 25);
  Vida2D::Vector2 size(50, 50);

  Vida2D::Render::SetBackgroundColor(Vida2D::Color(20, 20, 20, 255));

  while (Vida2D::Running()) {
    Vida2D::PollEvents();
    Vida2D::ClearScreen();

    Vida2D::Render::SetColor(Vida2D::Red);
    Vida2D::Render::RectFill(first_pos, size);

    Vida2D::Render::SetColor(Vida2D::Blue);
    Vida2D::Render::RectFill(first_pos.TranslatedX(75), size);

    Vida2D::Render::SetColor(Vida2D::Green);
    Vida2D::Render::RectFill(first_pos.TranslatedX(75 * 2), size);

    Vida2D::Render::Update();
  }
}
```
