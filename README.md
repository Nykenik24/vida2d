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
#include "vida2d.h"
#include "vida2d/render.h"
#include "vida2d/vec.h"

int main(void) {
  if (!vida2d_init("test", 800, 600))
    return 1;

  while (vida2d_running()) {
    vida2d_poll_events();
    vida2d_clear();

    vida2d_vec2_t first_pos = vida2d_vec2(25, 25);
    vida2d_set_color(vida2d_red);
    vida2d_draw_rect(V2D_DRAW_FILLED, vida2d_vec2(25, 25), vida2d_vec2(50, 50));

    vida2d_set_color(vida2d_green);
    vida2d_draw_rect(V2D_DRAW_FILLED, vida2d_vec_transformx(first_pos, 75),
                     vida2d_vec2(50, 50));

    vida2d_set_color(vida2d_blue);
    vida2d_draw_rect(V2D_DRAW_FILLED, vida2d_vec_transformx(first_pos, 75 * 2),
                     vida2d_vec2(50, 50));

    vida2d_present();
  }

  vida2d_close();
  return 0;
}
```
