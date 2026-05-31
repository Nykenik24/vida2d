#include "vida2d/render/text.hpp"
#include "SDL3/SDL_stdinc.h"
#include "vida2d.hpp"
#include "vida2d/color.hpp"
#include "vida2d/render/render.hpp"
#include "vida2d/time/time.hpp"
#include "vida2d/vec.hpp"
#include <iostream>
#include <unistd.h>

Vida2D::Color RandomColor() {
  static const Vida2D::Color colors[] = {
      Vida2D::White,
      Vida2D::Red,
      Vida2D::Green,
      Vida2D::Blue,
      Vida2D::Color(128, 0, 128, 255), // Purple
      Vida2D::Color(255, 255, 0, 255), // Yellow
  };
  return colors[SDL_rand(6)];
}

int rand_range(int min, int max) {
  int n = SDL_rand(max);
  return n >= min ? n : min;
}

int main(void) {
  Vida2D::Context::Init("test", 800, 600);

  Vida2D::Render::SetBackgroundColor(Vida2D::Color(20, 20, 20, 255));

  Vida2D::Render::Font font("assets/font.ttf", 24);
  Vida2D::Render::Font debug_font("assets/font.ttf", 12);
  Vida2D::Render::Text label(font, "Hello, World!", Vida2D::Red);

  Vida2D::Time::Timer timer(1);

  Vida2D::Render::Text debug_info(debug_font, "");

  Vida2D::Vector2 pos(0, 0);

  while (Vida2D::Running()) {
    Vida2D::PollEvents();
    Vida2D::ClearScreen();

    label.Draw(pos);

    debug_info.SetStringF(
        "Duration: %.1f\nLeft: %.1f\nElapsed: %.1f\n\nPos: %.0f, %.0f",
        timer.GetDuration(), timer.Left(), timer.Elapsed(), pos.x, pos.y);
    debug_info.Draw(Vida2D::Vector2(5, 5));

    if (timer.Done()) {
      label.SetColor(RandomColor());
      font.SetSize(rand_range(24, 48));
      pos = Vida2D::Vector2(rand_range(50, 700), rand_range(50, 500));
      timer.SetDuration(rand_range(1, 4));
    }

    Vida2D::Render::Update();
    Vida2D::Update();
  }
}
